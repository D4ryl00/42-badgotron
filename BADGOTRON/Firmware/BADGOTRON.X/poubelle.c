
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
