#include "badgotron.h"

t_wiegand_buf	g_wiegand_buf;

void	init_wiegand(void)
{
	u8	tmp = 0;
	
	// Init buffer
	g_wiegand_buf.index = 0;
	__builtin_disable_interrupts(); // Desativer les interrupts partout
	WIEGAND_DATA0_DIGITAL = 1; //Force la pin en mode digital (car elle est AN aussi la salope
	WIEGAND_DATA1_DIGITAL = 1; // idem

	WIEGAND_DATA0_MODE = PIN_MODE_INPUT;
	WIEGAND_DATA1_MODE = PIN_MODE_INPUT;
	WIEGAND_DATA0_CN = 1; //Enable CN6 (cf datasheet CN6 = RB4)
	WIEGAND_DATA1_CN = 1;
	CNCONbits.ON = 1; //Enable CON (CN interrupts)

	////CNPUEbits.CNPUE7 = 1; -> pull up DESACTIVE
	// READ PORT BIT FOR CLEARING IT
	tmp += WIEGAND_DATA0_DATA;
	tmp += WIEGAND_DATA1_DATA;
	// INTERRUPT
	IPC6bits.CNIP = 7;
	IPC6bits.CNIS = 3;
	IFS1bits.CNIF = 0;
	IEC1bits.CNIE = 1;
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

static void	badge_known_user(s16 index_position)
{
	u32	data_user_page_address;
	u8	user_data_position;

	g_flash_index.index.user[index_position].inactive = 0;
	flash_put_multibytes(g_flash_index.index.page_number * FLASH_PAGE_SIZE, g_flash_index.page, FLASH_PAGE_SIZE);
	data_user_page_address = db_get_user_data_page_address(g_flash_index.index.page_number, index_position);
	user_data_position = db_get_user_data_position(g_flash_index.index.page_number, index_position);
	db_get_data_page(data_user_page_address);
	if (!g_flash_data.data.user[user_data_position].timestamp)
		{
			g_flash_data.data.user[user_data_position].timestamp = get_timestamp();
			display_printstr("Bienvenue Jennifer");
		}
	else
	{
		display_printstr("Au revoir Jennifer  ");
		putnbr((get_timestamp() - g_flash_data.data.user[user_data_position].timestamp) / 60);
		display_printstr(" mn.");
		db_update_user_out_time(&(g_flash_data.data.user[user_data_position]));
		putnbr(g_flash_data.data.user[user_data_position].current_day);
		display_printstr("mn aujourd'hui.");
	}
	flash_put_multibytes(data_user_page_address, g_flash_data.page, FLASH_PAGE_SIZE);
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
	display_printstr("Bienvenue exInconnu");
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
	msleep(5000);
	display_clear();
}
