#include "badgotron.h"

void	__ISR(_TIMER_4_VECTOR, IPL7AUTO) Servo_PWM(void)
{
	PIN_SERVO_WRITE = 0;
	IFS0bits.T4IF = 0;
}

void	init_servo(u8 servo_position_percent)
{
 int cpt = 0;
    /* Initialize Timer4 = 0.01ms */
    T4CONbits.ON = 0;
    TMR4 = 0;
    T4CONbits.TCKPS = 0x03; // 1/8 => 5 million per second
    PR4 = 5000 + (10)*(servo_position_percent); // 1000 * % = 10
    IFS0bits.T4IF = 0;
	PIN_SERVO_WRITE = 0;
	PIN_SERVO_MODE = 0;
	PIN_SERVO_WRITE = 1;
	T4CONbits.ON = 1;
	IEC0bits.T4IE = 0;
    IFS0bits.T4IF = 0;
    IPC4bits.T4IP = 7;
    IPC4bits.T4IS = 0;
    IEC0bits.T4IE = 1;
}

void	end_servo(void)
{
	T4CONbits.ON = 0;
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