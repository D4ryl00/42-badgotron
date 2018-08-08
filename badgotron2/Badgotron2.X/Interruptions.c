#include "badgotron.h"

static void	interrupt_badge(void)
{
	wiegand_timer_init();
	while (g_wiegand_buf.index != 44)
	{
		if (WIEGAND_TIMER_FLAG == 1)
		{
			wiegand_timer_stop();
			g_wiegand_buf.index = 0;
			msleep(500);
			return ;
		}
		while (WIEGAND_DATA0_DATA && WIEGAND_DATA1_DATA && !WIEGAND_TIMER_FLAG);
		if (!WIEGAND_DATA0_DATA && !WIEGAND_TIMER_FLAG)
			g_wiegand_buf.buffer[g_wiegand_buf.index++] = 0;
		else if (!WIEGAND_DATA1_DATA)
			g_wiegand_buf.buffer[g_wiegand_buf.index++] = 1;
		while (!WIEGAND_TIMER_FLAG && !WIEGAND_DATA0_DATA || !WIEGAND_DATA1_DATA);
	}
	if (g_wiegand_buf.index == 44 && WIEGAND_DATA0_DATA && WIEGAND_DATA1_DATA)
	{
		g_print_enable = 1;
		g_wiegand_buf.index = 0;
		if (g_history)
		{
			// Enable interrupt for the button
			IFS1bits.CNAIF = 0;
			__builtin_enable_interrupts();
			history_timer_stop();
			show_history();
		}
		else
			start_badge();
	}
	wiegand_timer_stop();
}

static void	interrupt_rtc(void)
{
	rtc_update_time();
	display_clear();
	display_printstr("    Maintenance     ");
	if (!g_rtc_time.minutes && !g_rtc_time.hour	&& g_rtc_time.date == 0x01
			&& ((g_rtc_time.month == 0x01) || (g_rtc_time.month == 0x04)
			|| (g_rtc_time.month == 0x07) || (g_rtc_time.month == 0x10))
			|| (get_timestamp() - rtc_eereadword(RTC_TRIMESTER_UPDATE_TS) > (56246400 + 3600)))
	{
		display_printstr("     Trimestre      ");
		db_foreach(&trimesterly_task);
		rtc_eeputword(RTC_TRIMESTER_UPDATE_TS, get_timestamp());
	}
	else if ((!g_rtc_time.minutes && !g_rtc_time.hour
			&& g_rtc_time.date == 0x01)
			|| (get_timestamp() - rtc_eereadword(RTC_MONTH_UPDATE_TS) > (18748800 + 3600)))
	{
		display_printstr("        Mois        ");
		db_foreach(&monthly_task);
		rtc_eeputword(RTC_MONTH_UPDATE_TS, get_timestamp());
	}
	else if ((!g_rtc_time.minutes && !g_rtc_time.hour && g_rtc_time.day == 0x01)
			|| (get_timestamp() - rtc_eereadword(RTC_WEEK_UPDATE_TS) > (604800 + 3600)))
	{
		display_printstr("      Semaine       ");
		db_foreach(&weekly_task);
		rtc_eeputword(RTC_WEEK_UPDATE_TS, get_timestamp());
	}
	else if ((!g_rtc_time.minutes && !g_rtc_time.hour)
			|| (get_timestamp() - rtc_eereadword(RTC_DAY_UPDATE_TS) > (86400 + 3600)))
	{
		display_printstr("        Jour        ");
		db_foreach(&daily_task);
		rtc_eeputword(RTC_DAY_UPDATE_TS, get_timestamp());
	}
	display_clear();
	// Disable RTC flag
	rtc_disable_alarm_flag();
}

static void	interrupt_button(void)
{
	// msleep for display bug
	msleep(50);
	display_clear();
	if (g_button_enable == 1)
	{
		display_printstr("     Historique     ");
		display_printstr("     badgez...      ");
		g_history = 1;
		g_print_enable = 0;
	}
	if (g_button_enable == 2)
		show_history_pagetwo();
	g_button_enable = 0;
	history_timer_init();
}

void	__ISR(_CHANGE_NOTICE_VECTOR, IPL7AUTO) CN_Int(void) // Routine interruptions CN generale ( il convient apres de tester laquelle des pins a genere le flag
{
	__builtin_disable_interrupts();
	if (!RTC_PIN_MFP_READ)
		interrupt_rtc();
	else if (!BUTTON_PIN_READ && g_button_enable)
		interrupt_button();
	else if (!WIEGAND_DATA0_DATA || !WIEGAND_DATA1_DATA)
		interrupt_badge();
	IFS1bits.CNAIF = 0;
	IFS1bits.CNCIF = 0;
	__builtin_enable_interrupts();
}

void	__ISR(_UART_1_VECTOR, IPL7AUTO) Int_UART1_RX(void)
{
	uart_getstr();
	IFS1bits.U1RXIF = 0;
}

void	__ISR(_TIMER_5_VECTOR, IPL6AUTO) history_timer_Int(void)
{
	__builtin_disable_interrupts();
	g_history = 0;
	g_print_enable = 1;
	g_button_enable = 1;
	IFS0bits.T5IF = 0;
	history_timer_stop();
	__builtin_enable_interrupts();
	display_clear();
	set_pwm(0);
	set_led_r(0);
	set_led_g(0);
}