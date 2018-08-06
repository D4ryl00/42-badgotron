#include "badgotron.h"

void    set_mode_data_pins(u8 mode)
{
	DB0_MODE = mode;
	DB1_MODE = mode;
	DB2_MODE = mode;
	DB3_MODE = mode;
	DB4_MODE = mode;
	DB5_MODE = mode;
	DB6_MODE = mode;
	DB7_MODE = mode;
}

void    set_data_pins(u8 data)
{
	union u_u8 value;

	value.allBits = data;
	DB0_WRITE = value.bit0;
	DB1_WRITE = value.bit1;
	DB2_WRITE = value.bit2;
	DB3_WRITE = value.bit3;
	DB4_WRITE = value.bit4;
	DB5_WRITE = value.bit5;
	DB6_WRITE = value.bit6;
	DB7_WRITE = value.bit7;
}

/*void    set_data_pins(u8 data)
{
	LATDCLR = 0b11111111;
	LATDSET = data;
}*/

//void	write_init_command(u8 d)
//{
//	char	t;
//
//	t = DISPLAY_DELAY;
//	while (t--);
//	RS_WRITE = 0;
//	RW_WRITE = 0;
//	set_data_pins(d);
//	t = DISPLAY_DELAY;
//	while (t--);
//	E_WRITE = 1;
//	t = DISPLAY_DELAY2;
//	while (t--);
//	E_WRITE = 0;
//}

void	write_command(u8 d)
{
	u16	t;

	RS_WRITE = 0;
	RW_WRITE = 0;
	t = 2;
	while (t--);
	E_WRITE = 1;
	t = 4;
	while (t--);
	set_data_pins(d);
	t = 4;
	while (t--);
	E_WRITE = 0;
	t = 12;
	while (t--);
}

//void	display_printchar(u8 d)
//{
//	char	t;
//
//	t = DISPLAY_DELAY;
//	while (t--);
//	RS_MODE = 0;
//	RS_WRITE = 1;
//	RW_MODE = 0;
//	RW_WRITE = 0;
//	set_data_pins(d);
//	t = DISPLAY_DELAY;
//	while (t--);
//	E_WRITE = 1;
//	t = DISPLAY_DELAY2;
//	while (t--);
//	E_WRITE = 0;
//}

void	display_printchar(u8 d)
{
	u16	t;

	if (g_print_enable == 0)
		return ;
	RS_WRITE = 1;
	RW_WRITE = 0;
	t = 2;
	while (t--);
	E_WRITE = 1;
	set_data_pins(d);
	t = 50;
	while (t--);
	E_WRITE = 0;
	t = 42;
	while (t--);
}

void	display_returnhome(void)
{
	write_command(0x02); // Display clear
	msleep(2);
}

void    display_printstr(u8 str[])
{
	int i = 0;
	while (str[i])
		display_printchar(str[i++]);
}

void	display_print()
{
	u8	i;

	display_returnhome();
	i = -1;
	while (++i < 20)
		display_printchar(g_display_str[i]);
	i = -1;
	while (++i < 20)
		display_printchar(g_display_str[40 + i]);
	i = -1;
	while (++i < 20)
		display_printchar(g_display_str[20 + i]);
	i = -1;
	while (++i < 20)
		display_printchar(g_display_str[60 + i]);
}

void	display_clear(void)
{
	write_command(0x01); // Display clear
	msleep(2);
}

void    display_init(void)
{
	// Init transcever direction
	TS_TR_MODE = PIN_MODE_OUTPUT;
	TS_TR_WRITE = 0;
	
	E_MODE = 0;
	RW_MODE = 0;
	RS_MODE = 0;
	E_WRITE = 0;
	set_mode_data_pins(0);
	msleep(15); // 50 ms because VDD < 4.5V
	// Init start
	write_command(0x30);
	msleep(5);
	write_command(0x30);
	msleep(1);
	write_command(0x30);
	msleep(1);
	write_command(0x38); // Number of lines and character font
	msleep(1);
	write_command(0x08); // Display off
	msleep(1);
	write_command(0x01); // Display clear
	msleep(1);
	write_command(0x06); // Entry mode set
	msleep(1);
	write_command(0x0c); // Display on, cursor on
	msleep(1);
}

