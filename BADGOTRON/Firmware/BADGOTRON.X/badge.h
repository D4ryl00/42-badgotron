/* 
 * File:   badge.h
 * Author: bocal
 *
 * Created on June 12, 2018, 9:32 AM
 */

#ifndef BADGE_H
#define	BADGE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define WIEGAND_DATA0_MODE TRISBbits.TRISB4
#define WIEGAND_DATA0_DATA PORTBbits.RB4
#define WIEGAND_DATA0_DIGITAL AD1PCFGbits.PCFG4
#define WIEGAND_DATA0_CN CNENbits.CNEN6

#define WIEGAND_DATA1_DATA PORTBbits.RB5
#define WIEGAND_DATA1_MODE TRISBbits.TRISB5
#define WIEGAND_DATA1_DIGITAL AD1PCFGbits.PCFG5
#define WIEGAND_DATA1_CN CNENbits.CNEN7

typedef struct	s_wiegand_buf
{
    u8			index;
    u8			buffer[44];
}				t_wiegand_buf;

extern t_wiegand_buf	g_wiegand_buf;

#ifdef	__cplusplus
}
#endif

#endif	/* BADGE_H */

