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

void    set_data_pins(u8 value)
{
	DB0_WRITE = value & 0b00000001;
	DB1_WRITE = value & 0b00000010;
	DB2_WRITE = value & 0b00000100;
	DB3_WRITE = value & 0b00001000;
	DB4_WRITE = value & 0b00010000;
	DB5_WRITE = value & 0b00100000;
	DB6_WRITE = value & 0b01000000;
	DB7_WRITE = value & 0b10000000;
}

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

void	write_data(u8 d)
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
}

void    display_init(void)
{
	E_WRITE = 0;
	E_MODE = 0;
	set_mode_data_pins(0);
	msleep(50); // 50 ms because VDD < 4.5V
	// Init start
	write_init_command(0x30);
	msleep(50);
	write_command(0x30);
	msleep(50);
	write_command(0x38); // Number of lines and character font
	msleep(50);
	write_command(0x0c); // Display off
	msleep(50);
	write_command(0x06); // Entry mode set
	msleep(50);
	write_command(0x01); // Display clear
	msleep(50);
	//init end
	// Set cursor to Home
	set_data_pins(0b00000010); // Entry mode set
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	// test put A
	RS_WRITE = 1;
	RW_WRITE = 0;
	set_data_pins(0b01000001);
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
}

/*void    display_init(void)
{
	E_WRITE = 0;
	RW_WRITE = 0;
	RS_WRITE = 0;
	E_MODE = 0;
	RW_MODE = 0;
	RS_MODE = 0;
	set_data_pins(0);
	set_mode_data_pins(0);
	msleep(50); // 50 ms because VDD < 4.5V
	// Init start
	DB5_WRITE = 1;
	DB4_WRITE = 1;
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	set_data_pins(0b00111100); // Number of lines and character font
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	set_data_pins(0b00001000); // Display off
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	set_data_pins(0b00000001); // Display clear
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	set_data_pins(0b00000110); // Entry mode set
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	//init end
	// Set cursor to Home
	set_data_pins(0b00000010); // Entry mode set
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
	// test put A
	RS_WRITE = 1;
	RW_WRITE = 0;
	set_data_pins(0b01000001);
	E_WRITE = 1;
	E_WRITE = 0;
	msleep(50);
}*/