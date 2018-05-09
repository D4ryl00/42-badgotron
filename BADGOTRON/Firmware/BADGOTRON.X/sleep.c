#include "types.h"
#include "struct.h"
#include "macros.h"
#include <p32xxxx.h>
#include <xc.h>

u32 get_ten_power(u8 mul)
{
    u32 res;
    u8  i;

    res = 1;
    i = -1;
    while (++i < mul)
        res *= 10;
    return (res);
}

void    inc_nano(t_nanotime *mytime)
{
    if (mytime->nano >= 999)
    {
        mytime->nano = 0;
        inc_micro(mytime);
    }
    else
        mytime->nano++;
}

void    inc_micro(t_nanotime *mytime)
{
    if (mytime->micro >= 999)
    {
        mytime->micro = 0;
        inc_milli(mytime);
    }
    else
        mytime->micro++;
}

void    inc_milli(t_nanotime *mytime)
{
    if (mytime->milli >= 999)
    {
        mytime->milli = 0;
        inc_second(mytime);
    }
    else
        mytime->milli++;
}

void    inc_second(t_nanotime *mytime)
{
    if (mytime->second >= 999)
    {
        mytime->second = 0;
        inc_minute(mytime);
    }
    else
        mytime->second++;
}

void    inc_minute(t_nanotime *mytime)
{
    mytime->minute++;
}

/* time is in millisecond */
void    msleep(u32 time)
{
    int cpt = 0;
    /* Initialize Timer2 = 1s */
    T2CONbits.ON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0; // / 1 million per second
    PR2 = 1000; // = 1 ms
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while (time > cpt)
    {
        if (IFS0bits.T2IF)
        {
            cpt++;
            IFS0bits.T2IF = 0;
        }
    }
    T2CONbits.ON = 0;
}

void    clock_sleep(u32 time)
{
    int cpt = 0;
    /* Initialize Timer2 = 1s */
    T2CONbits.ON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0; // / 1 million per second
    PR2 = time; // = 1 ms
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while (!IFS0bits.T2IF)
    {
    }
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 0;
}