#include "badgotron.h"

void	button_init(void)
{
	u8	tmp;

	__builtin_disable_interrupts();
	BUTTON_PIN_MODE = PIN_MODE_INPUT;
	CNCONAbits.ON = 1; //Enable CON (CN interrupts)
	BUTTON_PIN_PULLUP = 0;
	BUTTON_PIN_CN = 1;
	// READ PORT BIT FOR CLEARING IT
	tmp = BUTTON_PIN_READ;
	// INTERRUPT
	IPC8bits.CNIP = 7;
	IPC8bits.CNIS = 3;
	IFS1bits.CNAIF = 0;
	IEC1bits.CNAIE = 1;
	__builtin_enable_interrupts();
}