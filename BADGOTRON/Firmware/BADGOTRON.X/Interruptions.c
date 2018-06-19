#include "badgotron.h"

void	__ISR(_CHANGE_NOTICE_VECTOR, IPL7) Int_Badge(void) // Routine interruptions CN generale ( il convient apres de tester laquelle des pins a genere le flag
{
	// ICI IL FAUDRA RETURN() SI INDEX == 44 (à savoir que le buffer n'est pas encore traite), et mettre la LED lecteur ROUGE
	if (!WIEGAND_DATA0_DATA)
		g_wiegand_buf.buffer[g_wiegand_buf.index++] = 0;
	else if (!WIEGAND_DATA1_DATA)
		g_wiegand_buf.buffer[g_wiegand_buf.index++] = 1;
	if (g_wiegand_buf.index == 44 && WIEGAND_DATA0_DATA && WIEGAND_DATA1_DATA)
	{
		display_clear();
		display_printstr("BADGE_OK_");
		u8	i = 0;
		while (i < 44)
		{
			u8	j = -1;
			u8	digit = 0;
			while (++j < 4)
				digit |= g_wiegand_buf.buffer[i++] << (3 - j);
				display_printchar("0123456789ABCDEF"[digit]);
		}
		g_wiegand_buf.index = 0;
		msleep(5000);
	}
	IFS1bits.CNIF = 0;
}

void	__ISR(_UART_1_VECTOR, IPL7) Int_UART1_RX(void)
{
	uart_getstr();
	IFS0bits.U1RXIF = 0;
}