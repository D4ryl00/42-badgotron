/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on May 9, 2018, 2:50 PM
 */

#include "badgotron.h"
u8				g_set_time;
u8				g_display_str[80] = {' '};
u8				g_print_time = 1;
t_flash_page	g_flash_index;
t_flash_page	g_flash_data;
// badge_mode drop the day timestamp at midnight if the user is not logged out
// like the current badger.
u8				g_badger_mode = 1;
u8				g_history = 0;
u8				g_button_enable = 1;

void    print_uartbuffer(void)
{
    display_printstr(g_uart_rx_buf.buffer);
    uart_clear_buffer();
}

void	print_bin(u8 byte)
{
    display_printchar((byte & 0b10000000) ? '1' : '0');
    display_printchar((byte & 0b1000000) ? '1' : '0');
    display_printchar((byte & 0b100000) ? '1' : '0');
    display_printchar((byte & 0b10000) ? '1' : '0');
    display_printchar((byte & 0b1000) ? '1' : '0');
    display_printchar((byte & 0b100) ? '1' : '0');
    display_printchar((byte & 0b10) ? '1' : '0');
    display_printchar((byte & 0b1) ? '1' : '0');
}

void	putnbr(u32 nbr)
{
    u32	power;
    u32	tmp;

    tmp = nbr;
    power = 1;
    while ((nbr /= 10))
        power *= 10;
    nbr = tmp;
    while (power)
    {
        display_printchar("0123456789"[(nbr / power) % 10]);
        power /= 10;
    }
}

void	print_badge(u8 *id)
{
    u8	i;

    i= -1;
    while (++i < 5)
    {
        display_printchar("0123456789ABCDEF"[id[i] >> 4]);
        display_printchar("0123456789ABCDEF"[id[i] & 0x0f]);
    }
}

int main(int argc, char** argv)
{
    INTCONSET = _INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    display_init();
    init_uart();
    init_spi();
    /*flash_set_block_protection(FLASH_BLOCK_UNPROTECTED);
    flash_4k_erase(0x1000);
    flash_write(0x1000, 'A');
    flash_write(0x1001, 'Y');
    flash_write(0x1002, '!');
    flash_set_block_protection(FLASH_BLOCK_PROTECTED);*/
    //flash_put_byte(0x1002, '?');
    //flash_put_multibytes(0x1000, "Flash OK_", sizeof("Flash OK_") - 1);
    //flash_chiperase();
    /*tmp = flash_get_byte_init(0x1000);
    display_printchar(tmp);
    while ((tmp = flash_get_byte_next()) != 0xff)
        display_printchar(tmp);
    flash_get_byte_end();*/
    //tmp = rtc_get_id();
    //rtc_eewrite(0x00, 'U');
    //rtc_srwrite(0);
    g_set_time = 0;
    init_rtc(0);
    init_wiegand();
    button_init();
    NRJ_init();
    while (42)
    {
        WDTCONbits.WDTCLR = 1;
        if (!NRJ_PIN_READ)
        {
            __builtin_disable_interrupts();
            while (!NRJ_PIN_READ)
                WDTCONbits.WDTCLR = 1;
        }
        __builtin_enable_interrupts();
        if (g_print_time)
        {
            rtc_update_time();
            display_returnhome();
            print_time();
            display_printchar('_');
            print_bin(g_set_time);
            display_printchar('_');
            putnbr(get_timestamp());
            msleep(10);
        }
    }
    return (EXIT_SUCCESS);
}
