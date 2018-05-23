/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on May 9, 2018, 2:50 PM
 */

#include "badgotron.h"

int main(int argc, char** argv)
{
	display_init();
    while (42)
    {
		WDTCONbits.WDTCLR = 1;
    }
    return (EXIT_SUCCESS);
}

