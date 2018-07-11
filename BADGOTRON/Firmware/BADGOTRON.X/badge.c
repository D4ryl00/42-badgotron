#include "badgotron.h"

t_wiegand_buf	g_wiegand_buf;

void	init_wiegand(void)
{
	u8	tmp = 0;
	
	// Init buffer
	g_wiegand_buf.index = 0;
	__builtin_disable_interrupts(); // Desativer les interrupts partout
	AD1PCFGbits.PCFG4 = 1; //Force la pin en mode digital (car elle est AN aussi la salope
	AD1PCFGbits.PCFG5 = 1; // idem

	WIEGAND_DATA0_MODE = PIN_MODE_INPUT;
	WIEGAND_DATA1_MODE = PIN_MODE_INPUT;
	CNENbits.CNEN6 = 1; //Enable CN6 (cf datasheet CN6 = RB4)
	CNENbits.CNEN7 = 1;
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
static u8	checksum_is_ok(void)
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

static void	convert_format_id(u8 *dest, u8 *src)
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

void	start_badge(void)
{
	u8	id[5];
	s16	index_position;
	u32	data_user_page_address;
	u8	user_data_position;
	u8	checksum;

	if (!(checksum = checksum_is_ok()))
	{
		display_clear();
		display_printstr("Badge reading error!");
		msleep(2000);
		display_clear();
		return ;
	}
	display_clear();
	display_printstr("Badge OK");
	convert_format_id(id, g_wiegand_buf.buffer);
	if ((index_position = get_index_position_user(id, checksum)) >= 0)
	{
		data_user_page_address = get_user_data_page_address(g_flash_index.index.page_number, index_position);
		user_data_position = get_user_data_position(g_flash_index.index.page_number, index_position);
		display_printstr(",Known bagdePage ");
		putnbr(g_flash_index.index.page_number);
		display_printstr(", user ");
		putnbr(index_position);
		display_printstr(", page_address ");
		putnbr(data_user_page_address);
		display_printstr(", user_position ");
		putnbr(user_data_position);
	}
	else
	{
		if ((index_position = get_first_free_space(checksum)) < 0)
		{
			display_printstr("No enough memory");
			msleep(2000);
			display_clear();
			return ;
		}
		data_user_page_address = get_user_data_page_address(g_flash_index.index.page_number, index_position);
		user_data_position = get_user_data_position(g_flash_index.index.page_number, index_position);
		id_cpy(g_flash_index.index.user[index_position].id, id);
		g_flash_index.index.user[index_position].inactive = 0;
		flash_put_multibytes(g_flash_index.index.page_number * FLASH_PAGE_SIZE, g_flash_index.page, FLASH_PAGE_SIZE);
		display_printstr("            Unknown badge.      Registered page");
		putnbr(g_flash_index.index.page_number);
		display_printstr(", user ");
		putnbr(index_position);
		display_printstr(", data_position ");
		putnbr(data_user_page_address);
	}
	msleep(5000);
	display_clear();

	/*if (get_user_position() == -1)
		create_user();*/
}