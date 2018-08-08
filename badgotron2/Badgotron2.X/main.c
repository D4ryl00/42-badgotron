/*
 * File:   main.c
 * Author: bocal
 *
 * Created on May 9, 2018, 2:50 PM
 */

#include "badgotron.h"
u8				g_display_str[80] = {' '};
u8				g_print_enable = 1;
t_flash_page	g_flash_index;
t_flash_page	g_flash_data;
// badge_mode drop the day timestamp at midnight if the user is not logged out
// like the current badger.
u8				g_badger_mode = 1;
u8				g_history = 0;
u8				g_button_enable = 1;
// Button enable :
//					set to 0 when button is pressed to avoid detecting 23190 keypresses.
//					set to 1 during normal operation
//					set to 2 when already displaying time information relative to the user.
//						It then triggers page2.

void    print_uartbuffer(void)
{
    display_printstr(g_uart_rx_buf.buffer);
    uart_clear_buffer();
}

void	print_bin(u8 byte)
{
    display_printchar((byte & 0b10000000) ? '1' : '0');
    display_printchar((byte & 0b1000000) ? '1' : '0');
    display_printchar((byte & 0b100000) ? '1' : '0');
    display_printchar((byte & 0b10000) ? '1' : '0');
    display_printchar((byte & 0b1000) ? '1' : '0');
    display_printchar((byte & 0b100) ? '1' : '0');
    display_printchar((byte & 0b10) ? '1' : '0');
    display_printchar((byte & 0b1) ? '1' : '0');
}

void	putnbr(u32 nbr)
{
    u32	power;
    u32	tmp;

    tmp = nbr;
    power = 1;
    while ((nbr /= 10))
        power *= 10;
    nbr = tmp;
    while (power)
    {
        display_printchar("0123456789"[(nbr / power) % 10]);
        power /= 10;
    }
}

void	print_badge(u8 *id)
{
    u8	i;

    i= -1;
    while (++i < 5)
    {
        display_printchar("0123456789ABCDEF"[id[i] >> 4]);
        display_printchar("0123456789ABCDEF"[id[i] & 0x0f]);
    }
}

void	set_pps_pins(void)
{
	// Disable the protection
	//CFGCONbits.IOLOCK = 0;

	// SPI
	SDI2R = 0b0000; // PIN 30 (RPA2)
	ANSELAbits.ANSA1 = 0; // Disable the analog mode for AN1.
	RPA1R = 0b0100; // PIN 20 (RPA1)

	// UART
	ANSELBbits.ANSB13 = 0; // Disable the analog mode for AN11.
	U1RXR = 0b0011; // PIN 11 (RPB13)
	RPC5R = 0b0001; // PIN 38 (RPC5)
	
	// PWM
	ANSELCbits.ANSC0 = 0; // Disable the analog mode for AN6.
	RPC0R = 0b0101; // PIN 25 (RPC0)

	// LED_RG
	ANSELBbits.ANSB2 = 0;
	ANSELCbits.ANSC2 = 0;
	RPB2R = 0b0101;
	RPC2R = 0b0101;

	// Enable the protection
	CFGCONbits.IOLOCK = 1;
}

int main(int argc, char** argv)
{
	u8	tmp;
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
	set_pps_pins();
    display_init();
    init_uart();
    init_spi();
    /*flash_set_block_protection(FLASH_BLOCK_UNPROTECTED);
    flash_4k_erase(0x1000);
    flash_write(0x1000, 'A');
    flash_write(0x1001, 'Y');
    flash_write(0x1002, '!');
    flash_set_block_protection(FLASH_BLOCK_PROTECTED);*/
    //flash_put_byte(0x1002, '?');
    //flash_put_multibytes(0x1000, "Flash OK_", sizeof("Flash OK_") - 1);
    //flash_chiperase();
    /*tmp = flash_get_byte_init(0x1000);
    display_printchar(tmp);
    while ((tmp = flash_get_byte_next()) != 0xff)
        display_printchar(tmp);
    flash_get_byte_end();*/
    //tmp = rtc_get_id();
    //rtc_eewrite(0x00, 'U');
    //rtc_srwrite(0);
    init_rtc(1, 0, 0);
    init_wiegand();
    button_init();
    NRJ_init();
	init_pwm();
	init_led_rg();
    while (42)
    {
        WDTCONbits.WDTCLR = 1;
        if (!NRJ_PIN_READ)
        {
            __builtin_disable_interrupts();
            while (!NRJ_PIN_READ)
                WDTCONbits.WDTCLR = 1;
        }
        __builtin_enable_interrupts();
		if (g_print_enable)
		{
			WDTCONbits.WDTCLR = 1;
			rtc_update_time();
			display_returnhome();
			display_printstr("o-----");
			print_date();
			display_printstr("-----o");
			display_printstr("|    ");
			putnbr(get_timestamp());
			display_printstr("    |");
			display_printstr("|    BADG>OTRON    |");
			display_printstr("o-----");
			print_time();
			display_printstr("-----o");
			msleep(10);
		}
    }
    return (EXIT_SUCCESS);
}