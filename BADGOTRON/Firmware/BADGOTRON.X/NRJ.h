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

#define NRJ_PIN_DIGITAL AD1PCFGbits.PCFG2
#define NRJ_PIN_PULLUP CNPUEbits.CNPUE4
#define NRJ_PIN_MODE TRISBbits.TRISB1
#define NRJ_PIN_READ PORTBbits.RB1

#ifdef	__cplusplus
}
#endif

#endif	/* NRJ_H */

