
#include "types.h"
#include <p32xxxx.h>

int main(void)
{
    DEVCFG1bits.FNOSC = 011;
    DEVCFG1bits.POSCMOD = 10;
    DEVCFG2bits.FPLLIDIV = 2;
    DEVCFG2bits.FPLLMUL = 18;
    OSCCONbits.PLLODIV = 1;

    return (0);
}

