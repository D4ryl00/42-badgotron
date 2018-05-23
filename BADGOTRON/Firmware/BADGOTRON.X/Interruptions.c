#include <p32xxxx.h>
#include <xc.h>

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