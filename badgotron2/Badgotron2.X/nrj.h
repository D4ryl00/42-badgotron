/* 
 * File:   NRJ.h
 * Author: bocal
 *
 * Created on July 16, 2018, 2:12 PM
 */

#ifndef NRJ_H
#define	NRJ_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NRJ_PIN_ANALOG ANSELCbits.ANSC1
#define NRJ_PIN_PULLUP CNPUCbits.CNPUC1
#define NRJ_PIN_MODE TRISCbits.TRISC1
#define NRJ_PIN_READ PORTCbits.RC1
//#define NRJ_PIN_READ 1

#ifdef	__cplusplus
}
#endif

#endif	/* NRJ_H */

