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

