#include "badgotron.h"

t_wiegand_buf	g_wiegand_buf;

void	init_badge(void)
{
	u8	tmp;
	
	// Init buffer
	g_wiegand_buf.index = 0;
	__builtin_disable_interrupts(); // Desativer les interrupts partout

	BADGE_LED_R_MODE = PIN_MODE_OUTPUT;
	BADGE_LED_G_MODE = PIN_MODE_OUTPUT;
	BADGE_LED_R_WRITE = 1;
	BADGE_LED_G_WRITE = 0;

	WIEGAND_DATA0_MODE = PIN_MODE_INPUT;
	WIEGAND_DATA1_MODE = PIN_MODE_INPUT;
	WIEGAND_DATA0_CN = 1;
	WIEGAND_DATA1_CN = 1;
	CNCONAbits.ON = 1; //Enable CON (CN interrupts)
	CNCONCbits.ON = 1; //Enable CON (CN interrupts)

	////CNPUEbits.CNPUE7 = 1; -> pull up DESACTIVE
	// READ PORT BIT FOR CLEARING IT
	tmp = WIEGAND_DATA0_DATA;
	tmp = WIEGAND_DATA1_DATA;
	// INTERRUPT
	IPC8bits.CNIP = 7;
	IPC8bits.CNIS = 2;
	IFS1bits.CNAIF = 0;
	IEC1bits.CNAIE = 1;
	IFS1bits.CNCIF = 0;
	IEC1bits.CNCIE = 1;
	__builtin_enable_interrupts();
}
/* tested and working */
u8	checksum_is_ok(void)
{
	u8	res;
	u8	checksum;
	u8	i;
	u8	j;
	u8	tmp;
	
	res = 0;
	checksum = 0;
	i = -1;
	while (++i < 4)
		checksum = (checksum << 1) + g_wiegand_buf.buffer[40 + i];
	i = 0;
	while (i < 40)
	{
		tmp = 0;
		j = -1;
		while (++j < 4)
			tmp = (tmp << 1) + g_wiegand_buf.buffer[i + j];
		res ^= tmp;
		i += 4;
	}
	if (res == checksum)
		return (checksum);
	return (0);
}

void	convert_format_id(u8 *dest, u8 *src)
{
	u8	i;

	i = -1;
	while (++i < 5)
		dest[i] = 0;
	i = -1;
	while (++i < 40)
		if (src[i])
			dest[i / 8] |= src[i] << (7 - (i % 8));
}

static void	uart_put_hexa_id(u8 id[5])
{
	u8	i;
	u8	hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B' , 'C', 'D', 'E', 'F' };

	i = -1;
	while (++i < 5)
	{
		uart_putchar(hex[id[i] / 16]);
		uart_putchar(hex[id[i] % 16]);
	}
}

static void	print_firstname(s16 index_position, u8 len_display)
{
	u32	i;

	uart_clear_buffer();
	uart_putstr("name_");
	uart_put_hexa_id(g_flash_index.index.user[index_position].id);
	uart_putchar('\n');
	i = 5000000;
	while (!IFS1bits.U1RXIF && i)
		i--;
	if (IFS1bits.U1RXIF)
		uart_getstr();
	IFS1bits.U1RXIF = 0;
	if (i && g_uart_rx_buf.index > 2)
		display_center_printstr(g_uart_rx_buf.buffer, len_display);
	else
		display_center_printstr("   ", len_display);
	uart_clear_buffer();
}

static void	badge_known_user(s16 index_position)
{
	u32	data_user_page_address;
	u8	user_data_position;

	g_flash_index.index.user[index_position].inactive = 0;
	flash_put_multibytes(g_flash_index.index.page_number * FLASH_PAGE_SIZE, g_flash_index.page, FLASH_PAGE_SIZE);
	data_user_page_address = db_get_user_data_page_address(g_flash_index.index.page_number, index_position);
	user_data_position = db_get_user_data_position(g_flash_index.index.page_number, index_position);
	db_get_data_page(data_user_page_address);
	display_clear();
	if (!g_flash_data.data.user[user_data_position].timestamp)
		{
			g_flash_data.data.user[user_data_position].timestamp = get_timestamp();
			display_printstr("o------------------o");
			display_printstr("|");
			print_firstname(index_position, 18);
			display_printstr("|");
			display_printstr("|    Bienvenue     |");
			display_printstr("o------------------o");
		}
	else
	{
		db_update_user_out_time(&(g_flash_data.data.user[user_data_position]));
		display_printstr("o------------------o");
		display_printstr("|");
		print_firstname(index_position, 18);
		display_printstr("|");
		display_printstr("|     Au revoir    |");
		display_printstr("o------------------o");
		msleep(1000);
		display_printstr("o------------------o");
		display_printstr("|Trimestre  ");
		print_hours(g_flash_data.data.user[user_data_position].current_trimester, 2, 3);
		display_printstr("|");
		display_printstr("|Aujourd'hui");
		print_hours(g_flash_data.data.user[user_data_position].current_day, 2, 2);
		display_printstr("|");
		display_printstr("o------------------o");
	}
	flash_put_multibytes(data_user_page_address, g_flash_data.page, FLASH_PAGE_SIZE);
	__builtin_enable_interrupts();
	activate_vumeter(g_flash_data.data.user[user_data_position].timestamp, g_flash_data.data.user[user_data_position].sliding_days);
}

static void	badge_unknown_user(u8 *id, u8 checksum)
{
	s16	index_position;
	u32	data_user_page_address;
	u8	user_data_position;

	if ((index_position = get_first_free_space(checksum)) < 0)
	{
		display_printstr("No enough memory");
		msleep(2000);
		display_clear();
		return ;
	}
	id_cpy(g_flash_index.index.user[index_position].id, id);
	g_flash_index.index.user[index_position].inactive = 0;
	flash_put_multibytes(g_flash_index.index.page_number * FLASH_PAGE_SIZE, g_flash_index.page, FLASH_PAGE_SIZE);
	data_user_page_address = db_get_user_data_page_address(g_flash_index.index.page_number, index_position);
	user_data_position = db_get_user_data_position(g_flash_index.index.page_number, index_position);
	db_get_data_page(data_user_page_address);
	init_user_data(&(g_flash_data.data.user[user_data_position]));
	g_flash_data.data.user[user_data_position].timestamp = get_timestamp();
	flash_put_multibytes(data_user_page_address, g_flash_data.page, FLASH_PAGE_SIZE);
	display_printstr("o------------------o");
	display_printstr("|");
	print_firstname(index_position, 18);
	display_printstr("|");
	display_printstr("|    Bienvenue     |");
	display_printstr("o------------------o");
}

void	start_badge(void)
{
	u8	id[5];
	s16	index_position;
	u8	checksum;

	if (!(checksum = checksum_is_ok()))
	{
		display_clear();
		display_printstr("Erreur de lecture du badge.");
		msleep(2000);
		display_clear();
		return ;
	}
	display_clear();
	convert_format_id(id, g_wiegand_buf.buffer);
	if ((index_position = get_index_position_user(id, checksum)) >= 0)
		badge_known_user(index_position);
	else
		badge_unknown_user(id, checksum);
	//msleep(5000);
	g_print_enable = 0;
	history_timer_init();
	//display_clear();
}
