/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on May 9, 2018, 2:50 PM
 */

#include "badgotron.h"

/*
 * 
 */

void    init_pins(void)
{

}


int main(int argc, char** argv) {

    /* Initialize LED */
    LATFbits.LATF1 = 0;
    TRISFbits.TRISF1 = 0;

    while (42)
    {
        clock_sleep(10000);
        LATFINV = 2;
    }
    return (EXIT_SUCCESS);
}

