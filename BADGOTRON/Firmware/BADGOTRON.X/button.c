#include "badgotron.h"

void	button_init(void)
{
	u8	tmp;

	__builtin_disable_interrupts();
	BUTTON_PIN_DIGITAL = 1; // Enable digital mode because this PIN is also analog
	BUTTON_PIN_MODE = PIN_MODE_INPUT;
	CNCONbits.ON = 1; //Enable CON (CN interrupts)
	// !!!!!!!!!!!!!!! CHANGE PULLUP TO OFF !!!!!!!!!!!!
	BUTTON_PIN_PULLUP = 1;
	BUTTON_PIN_CN = 1;
	// READ PORT BIT FOR CLEARING IT
	tmp = BUTTON_PIN_READ;
	// INTERRUPT
	IPC6bits.CNIP = 7;
	IPC6bits.CNIS = 3;
	IFS1bits.CNIF = 0;
	IEC1bits.CNIE = 1;
	__builtin_enable_interrupts();
}