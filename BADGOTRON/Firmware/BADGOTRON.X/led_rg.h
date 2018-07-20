/* 
 * File:   led_rg.h
 * Author: bocal
 *
 * Created on July 20, 2018, 3:25 PM
 */

#ifndef LED_RG_H
#define	LED_RG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PIN_LED_V_MODE TRISDbits.TRISD2
#define PIN_LED_V_WRITE LATDbits.LATD2

#define PIN_LED_R_MODE TRISDbits.TRISD1
#define PIN_LED_R_WRITE LATDbits.LATD1

#ifdef	__cplusplus
}
#endif

#endif	/* LED_RG_H */

