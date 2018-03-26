
#include "types.h"
#include <p32xxxx.h>

/* Enable secondary oscillator */
#pragma config FSOSCEN = ON

int main(void)
{
    /* Warm-up period */
    while (!OSCCONbits.SOSCRDY);

    /* Initialize LED */
    LATFbits.LATF1 = 0;
    TRISFbits.TRISF1 = 0;

    /* Initialize Button */
    TRISDbits.TRISD8 = 1;

    /* Initialize Timer1 */
    T1CONbits.ON = 0;
    T1CONbits.TCS = 1;
    T1CONbits.TSYNC = 0;
    TMR1 = 0;
    T1CONbits.TCKPS = 0;
    PR1 = 0x7000;
    /* Interrupt configuration */
    /*IFS0bits.T1IF = 0;
    IPC1bits.IC1IP = 1;
    IPC1bits.IC1IS = 1;
    IEC0bits.T1IE = 1;*/
    /* Enable Timer2 */
    T1CONbits.ON = 1;

    int divider = 1;
    while (1)
    {
        if (!PORTDbits.RD8)
        {
            T1CONbits.ON = 0;
            TMR1 = 0;
            PR1 = 0x7000 / divider;
            divider = divider == 16 ? 1 : divider * 2;
            T1CONbits.ON = 1;
            while (!PORTDbits.RD8);
        }
        if (TMR1 == PR1)
            LATFINV = 2;
        //IFS0bits.T2IF = 0;
    }
    return (0);
}