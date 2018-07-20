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

void	daily_task(t_index_user *index, t_data_user *data, u8 is_parent);
void	weekly_task(t_index_user *index, t_data_user *data, u8 is_parent);
void	monthly_task(t_index_user *index, t_data_user *data, u8 is_parent);
void	trimesterly_task(t_index_user *index, t_data_user *data, u8 is_parent);
void	activate_vumeter(u32 timestamp, u16 sliding_days[7]);

#ifdef	__cplusplus
}
#endif

#endif	/* PROTOTYPES_H */

