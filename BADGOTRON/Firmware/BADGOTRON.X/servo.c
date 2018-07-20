#include "badgotron.h"

void	__ISR(_TIMER_1_VECTOR, IPL7AUTO) Servo_PWM(void)
{
	PIN_SERVO_WRITE = 0;
	IFS0bits.T1IF = 0;
}

void	init_servo(s16 servo_position_percent)
{
    /* Initialize Timer1 = 0.01ms */
    T1CONbits.ON = 0;
	/* Select internal clock */
	T1CONbits.TCS = 0;
    TMR1 = 0;
    T1CONbits.TCKPS = 0x01; // 1/8 => 5 million per second
    PR1 = 5 * (1000 + 10 * servo_position_percent); // 1000 * % = 10
    IFS0bits.T1IF = 0;
	PIN_SERVO_WRITE = 0;
	PIN_SERVO_MODE = 0;
	PIN_SERVO_WRITE = 1;
	T1CONbits.ON = 1;
	IEC0bits.T1IE = 0;
    IFS0bits.T1IF = 0;
    IPC1bits.T1IP = 7;
    IPC1bits.T1IS = 0;
    IEC0bits.T1IE = 1;
}

void	end_servo(void)
{
	T1CONbits.ON = 0;
	PIN_SERVO_WRITE = 0;
}

void	actuate_servo(s16 servo_position_percent)
{
	int i;
	
	i = 0;
	//init_servo(servo_position_percent);
	while (i < 15)
	{
	init_servo(servo_position_percent);
	msleep(20);
	//PIN_SERVO_WRITE = 1;
	i++;
	}
	end_servo();
}

void	init_pwm(u8 percent)
{
	OC1CONbits.ON = 0;
	T3CONbits.ON = 0;
	IEC0bits.T3IE = 0;
	IFS0bits.T3IF = 0;
	IPC3bits.T3IP = 5;
	IPC3bits.T3IS = 0;
	OC1CONbits.OCTSEL = 1;
	T3CONbits.TCKPS = 0b100;
	TMR3 = 0;
	PR3 = 50000;
	/* min: 0.6 ms, neutral: 1,40 ms, max: 2.40 ms */
	OC1RS = PWM_MIN_CYCLE + PWM_MAX_PERCENT_CYCLE * percent;
	OC1R = OC1RS;
	OC1CONbits.OCM = 0b110;
	IEC0bits.T3IE = 0;
	T3CONbits.ON = 1;
	OC1CONbits.ON = 1;
}

void	set_pwm(u8 percent)
{
	OC1RS = PWM_MIN_CYCLE + PWM_MAX_PERCENT_CYCLE * percent;
}