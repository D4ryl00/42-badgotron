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

#define TS_TR_MODE TRISBbits.TRISB5
#define TS_TR_WRITE LATBbits.LATB5

#define DB0_MODE TRISBbits.TRISB9
#define DB1_MODE TRISCbits.TRISC6
#define DB2_MODE TRISCbits.TRISC7
#define DB3_MODE TRISCbits.TRISC8
#define DB4_MODE TRISCbits.TRISC9
#define DB5_MODE TRISBbits.TRISB10
#define DB6_MODE TRISBbits.TRISB11
#define DB7_MODE TRISBbits.TRISB12
#define E_MODE TRISBbits.TRISB8
#define RS_MODE TRISBbits.TRISB6
#define RW_MODE TRISBbits.TRISB7

#define DB0_WRITE LATBbits.LATB9
#define DB1_WRITE LATCbits.LATC6
#define DB2_WRITE LATCbits.LATC7
#define DB3_WRITE LATCbits.LATC8
#define DB4_WRITE LATCbits.LATC9
#define DB5_WRITE LATBbits.LATB10
#define DB6_WRITE LATBbits.LATB11
#define DB7_WRITE LATBbits.LATB12
#define E_WRITE LATBbits.LATB8
#define RS_WRITE LATBbits.LATB6
#define RW_WRITE LATBbits.LATB7

#define DB0_READ PORTBbits.PORTB9
#define DB1_READ PORTCbits.PORTC6
#define DB2_READ PORTCbits.PORTC7
#define DB3_READ PORTCbits.PORTC8
#define DB4_READ PORTCbits.PORTC9
#define DB5_READ PORTBbits.PORTB10
#define DB6_READ PORTBbits.PORTB11
#define DB7_READ PORTBbits.PORTB12
#define E_READ PORTBbits.PORTB8
#define RS_READ PORTBbits.PORTB6
#define RW_READ PORTBbits.PORTB7


#ifdef	__cplusplus
}
#endif

#endif	/* PIN_SELECT_H */

