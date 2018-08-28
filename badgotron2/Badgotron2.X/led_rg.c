#include "badgotron.h"

void	init_led_rg(void)
{
	T3CONbits.ON = 0;
	IEC0bits.T3IE = 0;
	IFS0bits.T3IF = 0;
	T3CONbits.TCKPS = 0b100;
	TMR3 = 0;
	PR3 = 50000;
	T3CONbits.ON = 1;

	OC3CONbits.ON = 0;
	OC3CONbits.OCTSEL = 1;
	OC3RS = 0;
	OC3R = OC3RS;
	OC3CONbits.OCM = 0b110;
	OC3CONbits.ON = 1;

	OC4CONbits.ON = 0;
	OC4CONbits.OCTSEL = 1;
	OC4RS = 0;
	OC4R = OC4RS;
	OC4CONbits.OCM = 0b110;
	OC4CONbits.ON = 1;
}

void	set_led_r(u8 percent)
{
	OC3RS = 400 * percent;
}

void	set_led_g(u8 percent)
{
	OC4RS = 400 * percent;
}

void	set_led_rg(u8 percent)
{
	set_led_g(percent);
	set_led_g(100);
	set_led_r(100);
	set_led_r(100 - percent);
}