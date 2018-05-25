#include "badgotron.h"

void	uart_tx_putstr(u8 *string)
{
	u32 i;
	
	i = 0;
	while (string[i])
	{
		if (U1STAbits.UTXBF == 0)
		{
			U1TXREG = string[i];
			i++;
		}
	}
	return ;
}


void	init_uart_tx(u8 *string)
{


	// POUR PLUS TARD U1STAbits.URXEN = 1;
	//PBCLK = 1MHz
	//BAUD RATE CALCULATION
	// BAUD RATE = (PBCLK / (16 * (BaudRate)) -1
	U1MODEbits.BRGH = 0;
	U1BRG = ((1000000)/(16 * 1200)) - 1;
	U1MODEbits.PDSEL = 0;
	U1MODEbits.STSEL = 0;
	U1MODEbits.ON = 1;
	U1STAbits.UTXEN = 1;
	uart_tx_putstr(string);
}