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

int main(int argc, char** argv)
{
    u8	RX_UART_char;
    u8	RX_SPI_char;
	u8	id;

    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    display_init();
    display_printstr("INIT OK");
    init_uart();
    uart_putstr("salut gregoire ce projet est super\n");
	init_spi();
	id = flash_get_id();
	//id = flash_get_status_register();
	display_printchar((id & 0b10000000) ? '1' : '0');
	display_printchar((id & 0b1000000) ? '1' : '0');
	display_printchar((id & 0b100000) ? '1' : '0');
	display_printchar((id & 0b10000) ? '1' : '0');
	display_printchar((id & 0b1000) ? '1' : '0');
	display_printchar((id & 0b100) ? '1' : '0');
	display_printchar((id & 0b10) ? '1' : '0');
	display_printchar((id & 0b1) ? '1' : '0');
	//flash_set_block_protection(0);
	//flash_put_byte(0, 'U');
	//RX_SPI_char = flash_get_byte(0);
	//if (RX_SPI_char)
	//	display_printchar(RX_SPI_char);
    while (42)
    {
        WDTCONbits.WDTCLR = 1;
        if (g_uart_rx_buf.index)
			print_uartbuffer();
    }
    return (EXIT_SUCCESS);
}

