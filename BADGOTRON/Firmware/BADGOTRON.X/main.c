/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on May 9, 2018, 2:50 PM
 */

#include "badgotron.h"

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

int main(int argc, char** argv)
{
    u8	RX_UART_char;
	u8	tmp;

    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    display_init();
    display_printstr("Display OK_");
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
	tmp = flash_get_byte_init(0x1000);
	display_printchar(tmp);
	while ((tmp = flash_get_byte_next()) != 0xff)
		display_printchar(tmp);
	flash_get_byte_end();
	//tmp = rtc_get_id();
	//rtc_eewrite(0x00, 'U');
	//rtc_srwrite(0);
	init_rtc();
	init_badge();
	msleep(2000);
    while (42)
    {
        WDTCONbits.WDTCLR = 1;
		rtc_update_time();
		display_clear();
		print_time();
		msleep(500);
		/*if (g_uart_rx_buf.index)
			print_uartbuffer();*/
    }
    return (EXIT_SUCCESS);
}

