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

#ifdef	__cplusplus
}
#endif

#endif	/* STRUCT_H */

