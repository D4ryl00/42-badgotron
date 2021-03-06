/* 
 * File:   pin_select.h
 * Author: bocal
 *
 * Created on May 17, 2018, 11:20 AM
 */

#ifndef PIN_SELECT_H
#define	PIN_SELECT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DB0_MODE TRISBbits.TRISB1
#define DB1_MODE TRISEbits.TRISE2
#define DB2_MODE TRISEbits.TRISE3
#define DB3_MODE TRISDbits.TRISD3
#define DB4_MODE TRISDbits.TRISD4
#define DB5_MODE TRISDbits.TRISD5
#define DB6_MODE TRISDbits.TRISD6
#define DB7_MODE TRISDbits.TRISD7
#define E_MODE TRISDbits.TRISD9
#define RS_MODE TRISDbits.TRISD10
#define RW_MODE TRISDbits.TRISD11

#define DB0_WRITE LATBbits.LATB1
#define DB1_WRITE LATEbits.LATE2
#define DB2_WRITE LATEbits.LATE3
#define DB3_WRITE LATDbits.LATD3
#define DB4_WRITE LATDbits.LATD4
#define DB5_WRITE LATDbits.LATD5
#define DB6_WRITE LATDbits.LATD6
#define DB7_WRITE LATDbits.LATD7
#define E_WRITE LATDbits.LATD9
#define RS_WRITE LATDbits.LATD10
#define RW_WRITE LATDbits.LATD11

#define DB0_READ PORTBbits.PORTB1
#define DB1_READ PORTEbits.PORTE2
#define DB2_READ PORTEbits.PORTE3
#define DB3_READ PORTDbits.PORTD3
#define DB4_READ PORTDbits.PORTD4
#define DB5_READ PORTDbits.PORTD5
#define DB6_READ PORTDbits.PORTD6
#define DB7_READ PORTDbits.PORTD7
#define E_READ PORTDbits.PORTD9
#define RS_READ PORTDbits.PORTD10
#define RW_READ PORTDbits.PORTD11


#ifdef	__cplusplus
}
#endif

#endif	/* PIN_SELECT_H */

