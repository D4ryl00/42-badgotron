/* 
 * File:   struct.h
 * Author: bocal
 *
 * Created on May 9, 2018, 3:40 PM
 */

#ifndef STRUCT_H
#define	STRUCT_H

#ifdef	__cplusplus
extern "C" {
#endif

union u_u8
{
    u8 allBits;
    struct
	{
		u8	bit0    :1;
		u8	bit1    :1;
		u8	bit2    :1;
		u8	bit3    :1;
		u8	bit4    :1;
		u8	bit5    :1;
		u8	bit6    :1;
		u8	bit7    :1;
    };
};

typedef struct  s_nanotime
{
	u16 nano;
	u16 micro;
	u16 milli;
	u8  second;
	u8  minute;
}               t_nanotime;

/*
** It's a BCD format:
** seconds = 10 SECONDS for 4 first bits + SECONDS for 4 last bits
** e.g. 18 seconds -> 0x18
*/
typedef struct	s_rtc_time
{
	u8	seconds;
	u8	minutes;
	u8	hour;
	u8	day;
	u8	date;
	u8	month;
	u8	year;
}				t_rtc_time;

typedef struct	s_user
{
	u8	id[5];
	u8	active;
}				t_user;

#ifdef	__cplusplus
}
#endif

#endif	/* STRUCT_H */

