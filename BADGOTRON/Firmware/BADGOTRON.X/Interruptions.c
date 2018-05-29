#include <p32xxxx.h>
#include <xc.h>
#include "badgotron.h"

/*void	__ISR(_CHANGE_NOTICE_VECTOR, IPL7) Int_RB1(void) // Routine interruptions CN generale ( il convient apres de tester laquelle des pins a genere le flag
{
    if (PORTDbits.RD4)
        LATFbits.LATF1 = 1;

        /*if (LATFbits.LATF1 == 0)
            LATFbits.LATF1 = 1;
        else
            LATFbits.LATF1 = 0;*/
/*    IFS1bits.CNIF = 0; // flag remis a 0
}
*/

void	__ISR(_UART_1_VECTOR, IPL7) Int_UART1(void)
{
    if (IFS0bits.U1RXIF) // Si l'interruption vient d'un RX
    {
       g_uart_rx_buf.buffer[g_uart_rx_buf.index] = U1RXREG;
       g_uart_rx_buf.index++;
       IFS0bits.U1RXIF = 0;
    }
    if (IFS0bits.U1TXIF) // Si l'interruption vient d'un TX
        IFS0bits.U1TXIF = 0;
}

