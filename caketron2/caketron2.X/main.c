
#include "types.h"
#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
//#pragma config FSOSCEN = ON

u8  divider = 1;
u8  dimp = 1;
s8  dim_dir = 1;

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

void	__ISR	(_TIMER_3_VECTOR, IPL7) Int_LED_DIM(void)
{
    IFS0bits.T3IF = 0;
    while (TMR3 <= dimp * PR3 / 100)
        LATFbits.LATF1 = 1;
    LATFbits.LATF1 = 0;
}

void	__ISR	(_TIMER_4_VECTOR, IPL7) Int_LED_DIM_CHANGE(void)
{
    IFS0bits.T4IF = 0;
    if (dimp == 99 || dimp == 0)
        dim_dir *= -1;
    dimp += dim_dir;
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

    /* Initialize Timer2 = 1s */
    T2CONbits.ON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0b100;
    PR2 = 62500;

    /* TIMER2 Interrupt configuration */
    IEC0bits.T2IE = 0;
    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 7;
    IPC2bits.T2IS = 0;
    //IEC0bits.T2IE = 1;

    /* Initialize Timer3 */
    T3CONbits.ON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 0b100;
    PR3 = 625;

    /* TIMER3 Interrupt configuration */
    IEC0bits.T3IE = 0;
    IFS0bits.T3IF = 0;
    IPC3bits.T3IP = 7;
    IPC3bits.T3IS = 0;
    IEC0bits.T3IE = 1;

    /* Initialize Timer4 */
    T4CONbits.ON = 0;
    TMR4 = 0;
    T4CONbits.TCKPS = 0b100; // = /16
    PR4 = 3125; // 625 * 5

    /* TIMER4 Interrupt configuration */
    IEC0bits.T4IE = 0;
    IFS0bits.T4IF = 0;
    IPC4bits.T4IP = 7;
    IPC4bits.T4IS = 0;
    IEC0bits.T4IE = 1;

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
    T3CONbits.ON = 1;
    T4CONbits.ON = 1;

    while (1)
    {
	WDTCONbits.WDTCLR = 1;
    }
    return (0);
}