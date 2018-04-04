
#include "types.h"
#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
//#pragma config FSOSCEN = ON

int divider = 1;

/* Enable secondary oscillator */
void	__ISR	(_TIMER_2_VECTOR, IPL7) Int_LED(void)
{
    LATFINV = 2;
    IFS0bits.T2IF = 0;
}

void	__ISR	(_EXTERNAL_1_VECTOR, IPL7) Int_BUT(void)
{
    TMR2 = 0;
    divider = divider == 32 ? 1 : divider * 2;
    PR2 = 125000 / divider;
    IFS0bits.INT1IF = 0;
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

    /* Initialize Timer2 */
    T2CONbits.ON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 4;
    PR2 = 125000;

    /* TIMER2 Interrupt configuration */
    IEC0bits.T2IE = 0;
    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 7;
    IPC2bits.T2IS = 0;
    IEC0bits.T2IE = 1;

    /* Button Interrupt config*/
    IEC0bits.INT1IE = 0;
    IFS0bits.INT1IF = 0;
    IPC1bits.INT1IP = 7;
    IPC1bits.INT1IS = 2;
    IEC0bits.INT1IE = 1;

    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
   /* Enable Timer2 */
    T2CONbits.ON = 1;

    while (1)
    {
	WDTCONbits.WDTCLR = 1;
    }
    return (0);
}