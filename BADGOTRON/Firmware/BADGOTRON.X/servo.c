#include "badgotron.h"

void	__ISR(_TIMER_1_VECTOR, IPL7AUTO) Servo_PWM(void)
{
	PIN_SERVO_WRITE = 0;
	IFS0bits.T1IF = 0;
}

void	init_servo(u8 servo_position_percent)
{
 int cpt = 0;
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

void	actuate_servo(u8 servo_position_percent)
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