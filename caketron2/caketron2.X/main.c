
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
    TRISDbits.TRISD7 = 1;

    /* Initialize Timer2*/
    T2CONbits.ON = 0;
    T1CONbits.TCS = 1;
    T1CONbits.TSYNC = 1;
    T2CONbits.TCKPS = 3;
    TMR2 = 0;
    PR2 = 128;
    IPC2bits.IC2IP = 1;
    IPC2bits.IC2IS = 1;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;

    while (1)
    {
        while (!IFS0bits.T2IF);
        LATFbits.LATF1 = 1;
        IFS0bits.T2IF = 0;
        while (!IFS0bits.T2IF);
        LATFbits.LATF1 = 0;
        IFS0bits.T2IF = 0;
    }
    return (0);
}

