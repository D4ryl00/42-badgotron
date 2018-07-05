#include "types.h"
#include "struct.h"
#include "macros.h"
#include <p32xxxx.h>
#include <xc.h>

void    msleep(u32 time)
{
    int cpt = 0;
    /* Initialize Timer2 = 1s */
    T2CONbits.ON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0; // / 1 million per second
    PR2 = 1000; // = 1 ms
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
}

void    init_wiegand_timer(void)
{
    /* Initialize Timer3 = 1s */
    T3CONbits.ON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 3; // 1 million per second / 256
    PR3 = 9000; // +- 250 ms
    IFS0bits.T3IF = 0;
    T3CONbits.ON = 1;
}

void    stop_wiegand_timer(void)
{
    T3CONbits.ON = 0;
	IFS0bits.T3IF = 0;
}

void    clock_sleep(u32 time)
{
    int cpt = 0;
    /* Initialize Timer2 = 1s */
    T2CONbits.ON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0; // / 1 million per second
    PR2 = time; // = time us
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while (!IFS0bits.T2IF)
    {
    }
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 0;
}