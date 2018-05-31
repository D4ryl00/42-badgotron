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

    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    display_init();
    display_printstr("INIT OK");
    init_uart();
    uart_putstr("salut gregoire ce projet est super\n");
	init_spi();
	spi_putstr("U5", FLASH);
    while (42)
    {
        WDTCONbits.WDTCLR = 1;
        if (g_uart_rx_buf.index)
             print_uartbuffer();
    }
    return (EXIT_SUCCESS);
}

