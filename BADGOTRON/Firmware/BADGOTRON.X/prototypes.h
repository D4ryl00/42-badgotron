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
void	print_bin(u8 byte);

u8		daily_task(t_data_user *data);

#ifdef	__cplusplus
}
#endif

#endif	/* PROTOTYPES_H */

