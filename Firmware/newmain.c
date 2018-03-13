#include <p32xxxx.h>
#include <plib.h>
#include <stdlib.h>


#include <p32xxxx.h>

#define LED_D1     	    LATFbits.LATF2
#define LED_D1_DIR     	TRISFbits.TRISF2


#pragma config FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2

#define FOSC			72E6


void main(void)
{
	int i ;
TRISF = 0x0038;
TRISD = 0x0000;
TRISDbits.TRISD4 = 0;
//LATBbits.LATB0 = 1;
        while (42)
        {
            i = 0;
            while (i < 1000000)
           {
               i++;
            }
           PORTFbits.RF1 = 1;
           PORTDbits.RD4 = 1;
           //PORTBbits.RB0 = 1;
            i = 0;
          while (i < 5000000)
           {
                i++;
            }
          PORTFbits.RF1 = 0;
          PORTDbits.RD4 = 0;
          //PORTBbits.RB0 = 0;
        }

}
