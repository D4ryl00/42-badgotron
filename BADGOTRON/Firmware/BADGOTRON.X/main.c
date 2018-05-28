/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on May 9, 2018, 2:50 PM
 */

#include "badgotron.h"



int main(int argc, char** argv)
{
	u8	RX_UART_char;

	//display_init();
	 /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
	init_uart();
	uart_tx_putstr("salut gregoire ce projet est super");
    while (42)
    {
		WDTCONbits.WDTCLR = 1;
    }
    return (EXIT_SUCCESS);
}

