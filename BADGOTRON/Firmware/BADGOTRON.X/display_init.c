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

/*void    set_data_pins(u8 value)
{
	DB0_WRITE = value & 0b00000001;
	DB1_WRITE = value & 0b00000010 ? 1 : 0;
	DB2_WRITE = value & 0b00000100;
	DB3_WRITE = value & 0b00001000;
	DB4_WRITE = value & 0b00010000;
	DB5_WRITE = value & 0b00100000;
	DB6_WRITE = value & 0b01000000;
	DB7_WRITE = value & 0b10000000;
}*/

void	write_init_command(u8 d)
{
	char	t;

	t = DISPLAY_DELAY;
	RS_WRITE = 0;
	RS_MODE = 0;
	RW_WRITE = 0;
	RW_MODE = 0;
	set_data_pins(d);
	while (t--);
	E_WRITE = 1;
	E_WRITE = 0;
}

void	write_command(u8 d)
{
	char	t;

	t = DISPLAY_DELAY;
	while (t--);
	RS_WRITE = 0;
	RS_MODE = 0;
	RW_WRITE = 0;
	RW_MODE = 0;
	set_data_pins(d);
	t = DISPLAY_DELAY;
	while (t--);
	E_WRITE = 1;
	E_WRITE = 0;
}

void	display_printchar(u8 d)
{
	char	t;

	t = DISPLAY_DELAY;
	while (t--);
	RS_WRITE = 1;
	RS_MODE = 0;
	RW_WRITE = 0;
	RW_MODE = 0;
	set_data_pins(d);
	t = DISPLAY_DELAY;
	while (t--);
	E_WRITE = 1;
	E_WRITE = 0;
        msleep(50);
}

void    display_putstr(u8 str[])
{

        int i = 0;
        while (str[i])
            display_printchar(str[i++]);
}

void    display_init(void)
{
	E_WRITE = 0;
	E_MODE = 0;
	set_mode_data_pins(0);
	msleep(15); // 50 ms because VDD < 4.5V
	// Init start
	write_init_command(0x30);
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
	//init end

	// test put A
	//u8 str[] = "Salut Gregoire, ce projet est trop cool mais c'est un peu compliqu";
        /*if (str)
        {
            int i = 0;
            while (str[i])
            {
                display_printchar(str[i++]);
            }
            display_printchar(0xfc);
            msleep(50);
        }*/
}

