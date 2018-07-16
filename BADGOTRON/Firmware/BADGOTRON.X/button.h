/* 
 * File:   button.h
 * Author: bocal
 *
 * Created on July 16, 2018, 2:12 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BUTTON_PIN_DIGITAL AD1PCFGbits.PCFG2
#define BUTTON_PIN_CN CNENbits.CNEN4
#define BUTTON_PIN_PULLUP CNPUEbits.CNPUE4
#define BUTTON_PIN_MODE TRISBbits.TRISB2
#define BUTTON_PIN_READ PORTBbits.RB2

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */

