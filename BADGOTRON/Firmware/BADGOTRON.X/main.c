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

    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    display_init();
    display_printstr("INIT OK");
    init_uart();
	init_spi();
	uart_putstr("time_second?\n");

	//flash_set_block_protection(0);
	//print_bin(flash_get_status_register());
	//flash_4k_erase(0x1000);
	//flash_put_byte(0x1000, 'A');
	//flash_put_byte(0x1001, 'Y');
	display_printchar(flash_get_byte(0x1000));
	display_printchar(flash_get_byte(0x1001));
    while (42)
    {
        WDTCONbits.WDTCLR = 1;

		if (g_uart_rx_buf.index)
			print_uartbuffer();
    }
    return (EXIT_SUCCESS);
}

