#include "badgotron.h"

void	init_badge(void)
{
	u8	tmp = 0;

	// Init buffer
	g_wiegand_buf.index = 0;
	__builtin_disable_interrupts(); // Desativer les interrupts partout
	AD1PCFGbits.PCFG4 = 1; //Force la pin en mode digital (car elle est AN aussi la salope
	AD1PCFGbits.PCFG5 = 1; // idem

	WIEGAND_DATA0_MODE = PIN_MODE_INPUT;
	WIEGAND_DATA1_MODE = PIN_MODE_INPUT;
	CNENbits.CNEN6 = 1; //Enable CN6 (cf datasheet CN6 = RB4)
	CNENbits.CNEN7 = 1;
	CNCONbits.ON = 1; //Enable CON (CN interrupts)

	////CNPUEbits.CNPUE7 = 1; -> pull up DESACTIVE
	// READ PORT BIT FOR CLEARING IT
	tmp += WIEGAND_DATA0_DATA;
	tmp += WIEGAND_DATA1_DATA;
	// INTERRUPT
	IPC6bits.CNIP = 7;
	IPC6bits.CNIS = 3;
	IFS1bits.CNIF = 0;
	IEC1bits.CNIE = 1;
	__builtin_enable_interrupts();
}
