#include "badgotron.h"

void	init_pwm()
{
	OC1CONbits.ON = 0;
	T3CONbits.ON = 0;
	IEC0bits.T3IE = 0;
	IFS0bits.T3IF = 0;
	OC1CONbits.OCTSEL = 1;
	T3CONbits.TCKPS = 0b100;
	TMR3 = 0;
	PR3 = 50000;
	OC1RS = 0;
	OC1R = OC1RS;
	OC1CONbits.OCM = 0b110;
	T3CONbits.ON = 1;
	OC1CONbits.ON = 1;
}

void	set_pwm(u8 percent)
{
	/* min: 0.6 ms, neutral: 1,40 ms, max: 2.40 ms */
	OC1RS = PWM_MIN_CYCLE + PWM_MAX_PERCENT_CYCLE * (100 - percent - 3);
	percent = 0;
	/*if (percent < 60 && percent > 30)
		set_led_rg(percent + 40);
	else if (percent > 70 && percent < 85)
		set_led_rg(percent + 15);
	else if (percent > 85)
		set_led_rg(100);*/
}