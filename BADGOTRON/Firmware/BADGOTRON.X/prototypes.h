/* 
 * File:   prototypes.h
 * Author: bocal
 *
 * Created on May 17, 2018, 10:57 AM
 */

#ifndef PROTOTYPES_H
#define	PROTOTYPES_H

#ifdef	__cplusplus
extern "C" {
#endif


void    msleep(u32 time);
void    clock_sleep(u32 time);
void	uart_rx_parse(u8 c);
void	init_uart(void);
#ifdef	__cplusplus
}
#endif

#endif	/* PROTOTYPES_H */

