#include "badgotron.h"

void	uart_addcharbuffer(u8 c)
{
    g_uart_rx_buf.buffer[g_uart_rx_buf.index++] = c;
}

void	uart_addnullbuffer(void)
{
    g_uart_rx_buf.buffer[g_uart_rx_buf.index + 1] = '\0';
}

void    uart_clear_buffer(void)
{
    g_uart_rx_buf.index = 0;
}

void	uart_putstr(u8 *string)
{
	while (*string)
	{
		while (U1STAbits.UTXBF);
		U1TXREG = *string++;
	}
}
void	uart_getstr(void)
{
	u8	c;

	c = '0';
	while (c != '\n')
	{
		while (!U1STAbits.URXDA);
		c = U1RXREG & 0xFF;
		if (c == '\n')
			break ;
		uart_addcharbuffer(c);
	}
	uart_addnullbuffer();
}

void	init_uart(void)
{
	float	brg;

	// BAUD RATE CALCULATION
	// BAUD RATE = (PBCLK / (16 * (BaudRate)) - 1
	brg = ((float)PBCLK) / ((float)(4 * 19200)) - 1.0;
	if (brg - (unsigned int)brg >= 0.5)
		brg+=1.0;
	U1BRG = (u16)brg;
	U1MODEbits.BRGH = 1;
	U1MODEbits.PDSEL = 0;
	U1MODEbits.STSEL = 0;
	U1MODEbits.ON = 1;
	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;

	// INIT BUFFER FOR RX
	t_uart_rx_buf	g_uart_rx_buf;
	g_uart_rx_buf.index = 0;

	/*INITIALISATION INTERRUPTION UARTRX*/
	IPC6bits.U1IP = 7;
	IPC6bits.U1IS = 3;
	IFS0bits.U1RXIF = 0;
	IEC0bits.U1RXIE = 1;
}