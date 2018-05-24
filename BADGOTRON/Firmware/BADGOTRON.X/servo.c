#include "badgotron.h"


void	init_servo(void)
{
 int cpt = 0;
    /* Initialize Timer3 = 0.01ms */
    T2CONbits.ON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0; // / 1 million per second
    PR2 = 10; // = .01 ms
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while (cpt < time)
    {
        if (IFS0bits.T2IF)
        {
            cpt++;
            IFS0bits.T2IF = 0;
        }
    }
    T2CONbits.ON = 0;
}