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

void    set_all_data_pins(u8 value)
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

void    display_init(void)
{
	E_MODE = 0;
	RW_MODE = 0;
	RS_MODE = 0;
	E_WRITE = 0;
	RW_WRITE = 0;
	RS_WRITE = 0;
	set_all_data_pins(0);
	set_mode_data_pins(0);
	msleep(15);
	DB5_WRITE = 1;

}