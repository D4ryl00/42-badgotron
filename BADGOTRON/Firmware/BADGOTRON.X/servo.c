#include "badgotron.h"

void	__ISR(_TIMER_3_VECTOR, IPL7) Servo_PWM(void)
{
	PIN_SERVO_WRITE = 0;
	IFS0bits.T3IF = 0;
	return ;
}

void	init_servo(u8 servo_position_percent)
{
 int cpt = 0;
    /* Initialize Timer3 = 0.01ms */
    T3CONbits.ON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 0; // / 1 million per second
    PR3 = 1000 + (10)*(servo_position_percent); // 1000 * % = 10
    IFS0bits.T3IF = 0;
	PIN_SERVO_WRITE = 0;
	PIN_SERVO_MODE = 0;
	PIN_SERVO_WRITE = 1;
	T3CONbits.ON = 1;
	IEC0bits.T3IE = 0;
    IFS0bits.T3IF = 0;
    IPC3bits.T3IP = 7;
    IPC3bits.T3IS = 0;
    IEC0bits.T3IE = 1;
}

void	end_servo(void)
{
	T3CONbits.ON = 0;
	PIN_SERVO_WRITE = 0;
}

void	actuate_servo(u8 servo_position_percent)
{
	int i;
	
	i = 0;
	init_servo(servo_position_percent);
	while (i < 5)
	{
	init_servo(servo_position_percent);
	msleep(20);
	PIN_SERVO_WRITE = 1;
	i++;
	}
	end_servo();
}