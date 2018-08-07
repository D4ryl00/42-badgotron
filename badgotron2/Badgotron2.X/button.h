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

#define BUTTON_PIN_CN CNENAbits.CNIEA8
#define BUTTON_PIN_PULLUP CNPUAbits.CNPUA8
#define BUTTON_PIN_MODE TRISAbits.TRISA8
#define BUTTON_PIN_READ PORTAbits.RA8

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */

