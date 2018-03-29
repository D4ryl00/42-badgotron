
#include "types.h"
#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
//#pragma config FSOSCEN = ON

int divider = 1;
/* Enable secondary oscillator */
void	__ISR	(_TIMER_1_VECTOR, IPL7) Fonction(void)
{
    //T1CONbits.ON = 0;
    //TMR1 = 0;
    //PR1 = 0x8000 / divider;
    //T1CONbits.ON = 1;
    LATFINV = 2;
    IFS0bits.T1IF = 0;
}
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
    T1CONbits.TON = 0;
    T1CONbits.ON = 0;
    T1CONbits.TCS = 1;
    T1CONbits.TSYNC = 1;
    TMR1 = 0;
    T1CONbits.TCKPS = 0;
    PR1 = 0x8000;
    /* Interrupt configuration */
    IFS0bits.T1IF = 0;
    IPC1bits.T1IP = 7;
    IPC1bits.T1IS = 0;
    IEC0bits.T1IE = 1;
    //int divider = 1;
    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
        /* Enable Timer2 */
    T1CONbits.ON = 1;
    T1CONbits.TON = 1;
    while (1)
    {
        if (!PORTDbits.RD8)
        {
            //T1CONbits.ON = 0;
            TMR1 = 0;
            PR1 = 0x8000 / divider;
            divider = divider == 16 ? 1 : divider * 2;
	    LATFINV = 2;
            //T1CONbits.ON = 1;
            while (!PORTDbits.RD8)
	    {}
	    LATFINV = 2;
        }
	else
	{

	}
        //if (TMR1 == PR1)
          //  LATFINV = 2;
    }
    return (0);
}