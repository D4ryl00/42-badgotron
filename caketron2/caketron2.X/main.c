
#include "types.h"
#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
//#pragma config FSOSCEN = ON

u8 divider = 1;
u8  dimp = 25;

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

void	__ISR	(_TIMER_3_VECTOR, IPL7) Int_LED(void)
{
    IFS0bits.T3IF = 0;
    while (TMR3 < dimp * PR3 * 0,01)
        LATFbits.LATF1 = 1;
    LATFbits.LATF1 = 0;
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
    //IEC0bits.T2IE = 1;

    /* Initialize Timer3 */
    T3CONbits.ON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 4;
    PR3 = 2500;

    /* TIMER3 Interrupt configuration */
    IEC0bits.T3IE = 0;
    IFS0bits.T3IF = 0;
    IPC3bits.T3IP = 7;
    IPC3bits.T3IS = 0;
    IEC0bits.T3IE = 1;

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