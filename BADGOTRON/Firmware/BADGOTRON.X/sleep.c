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
    T2CONbits.TCKPS = 0x03; // 1/8 => 5 million per second
    PR2 = 5000; // = 1 ms
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

void    wiegand_timer_init(void)
{
    /* Initialize Timer1 = 1s */
    T3CONbits.ON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 7; // 1 million per second / 256
    PR3 = 39062; // +- 250 ms
    IFS0bits.T3IF = 0;
    T3CONbits.ON = 1;
}

void    wiegand_timer_stop(void)
{
    T3CONbits.ON = 0;
	IFS0bits.T3IF = 0;
}

void    history_timer_init(void)
{
    /* Initialize Timer4 et Timer5 in 32-bits mode */
    T4CONbits.ON = 0;
	T5CONbits.ON = 0;
	T4CONbits.T32 = 1;
	TMR4 = 0;
    TMR5 = 0;
    T4CONbits.TCKPS = 0x07; // div per 256
	PR4 = 781250; /* -> 5s */
	IFS0bits.T5IF = 0;
	IPC5bits.T5IP = 6;
	IPC5bits.T5IS = 0;
	IEC0bits.T5IE = 1;
    T4CONbits.ON = 1;
}

void    history_timer_stop(void)
{
    T4CONbits.ON = 0;
	IFS0bits.T5IF = 0;
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