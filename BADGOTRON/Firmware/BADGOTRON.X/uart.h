/* 
 * File:   uart.h
 * Author: bocal
 *
 * Created on May 31, 2018, 8:37 AM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct	s_uart_rx_buf
{
    u8			index;
    u8			buffer[512];
}				t_uart_rx_buf;

t_uart_rx_buf	g_uart_rx_buf;

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

