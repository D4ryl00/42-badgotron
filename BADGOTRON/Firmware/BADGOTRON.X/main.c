/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on May 9, 2018, 2:50 PM
 */

#include "badgotron.h"

void    print_uartbuffer(void)
{
    int i = 0;
    if (g_uart_rx_buf.index == 0)
        return ;
    while (i < g_uart_rx_buf.index)
    {
      display_printchar(g_uart_rx_buf.buffer[i]);
        i++;
    }
    uart_clear_buffer();
}

int main(int argc, char** argv)
{
    u8	RX_UART_char;

    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    display_init();
    display_putstr("INIT OK");
    init_uart();
    uart_tx_putstr("salut gregoire ce projet est super");
    while (42)
    {
        WDTCONbits.WDTCLR = 1;
        if (g_uart_rx_buf.index != 0)
             print_uartbuffer();
    }
    return (EXIT_SUCCESS);
}

