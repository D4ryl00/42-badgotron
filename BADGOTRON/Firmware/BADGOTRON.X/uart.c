#include "badgotron.h"

void    uart_clear_buffer(void)
{
    int i = 0;
    if (g_uart_rx_buf.index == 0)
        return ;
    while (i < g_uart_rx_buf.index + 5)
    {
        g_uart_rx_buf.buffer[i] = 0;
        i++;
    }
    g_uart_rx_buf.index = 0;

}

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

void	init_uart(void)
{


	// POUR PLUS TARD U1STAbits.URXEN = 1;
	//PBCLK = 1MHz
	//BAUD RATE CALCULATION
	// BAUD RATE = (PBCLK / (16 * (BaudRate)) -1
	U1MODEbits.BRGH = 0;
	U1BRG = ((PBCLK)/(16 * 4800)) - 1;
	U1MODEbits.PDSEL = 0;
	U1MODEbits.STSEL = 0;
	U1MODEbits.ON = 1;
	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;
	t_uart_rx_buf	g_uart_rx_buf;
	g_uart_rx_buf.index = 0;
	/*INITIALISATION INTERRUPTION UARTRX*/
	IPC6bits.U1IP = 7;
	IPC6bits.U1IS = 3;
	IFS0bits.U1RXIF = 0;
	IEC0bits.U1RXIE = 1;
	
}

u8	uart_rx(void)
{
	// ecrire dans g_RX_UART_CHAR[512]
	u8	c;
	c = 0;
	//while(!U1STAbits.URXDA);
	c = U1RXREG;
	return (c);
}

void	uart_rx_addcharbuffer(u8 c)
{
    g_uart_rx_buf.buffer[g_uart_rx_buf.index++] = c;
    g_uart_rx_buf.buffer[g_uart_rx_buf.index] = 0;
}