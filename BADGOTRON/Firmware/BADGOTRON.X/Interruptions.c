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
		g_wiegand_buf.index = 0;
		if (g_history)
			show_history();
		else
			start_badge();
	}
	wiegand_timer_stop();
}

static void	interrupt_rtc(void)
{
	rtc_update_time();
	display_clear();
	display_printstr("Maintenance         ");
	if (!g_rtc_time.seconds && !g_rtc_time.minutes && !g_rtc_time.hour
			&& g_rtc_time.date == 0x01 && ((g_rtc_time.month == 0x01)
			|| (g_rtc_time.month == 0x04) || (g_rtc_time.month == 0x07)
			|| (g_rtc_time.month == 0x10)))
	{
		display_printstr("start of trimester  ");
		db_foreach(&trimesterly_task);
	}
	else if (!g_rtc_time.seconds && !g_rtc_time.minutes && !g_rtc_time.hour
			&& g_rtc_time.date == 0x01)
	{
		display_printstr("start of month      ");
		db_foreach(&monthly_task);
	}
	else if (!g_rtc_time.seconds && !g_rtc_time.minutes && !g_rtc_time.hour
			&& g_rtc_time.day == 0x01)
	{
		display_printstr("start of week       ");
		db_foreach(&weekly_task);
	}
	else
	{
		display_printstr("start of day        ");
		db_foreach(&daily_task);
	}
	display_clear();
	// Disable RTC flag
	rtc_disable_alarm_flag();
}

static void	interrupt_button(void)
{
	display_clear();
	display_printstr("     Historique     ");
	display_printstr("     badgez...      ");
	g_history = 1;
	g_print_time = 0;
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
	IFS1bits.CNIF = 0;
	__builtin_enable_interrupts();
}

void	__ISR(_UART_1_VECTOR, IPL7AUTO) Int_UART1_RX(void)
{
	uart_getstr();
	IFS0bits.U1RXIF = 0;
}

void	__ISR(_TIMER_5_VECTOR, IPL6AUTO) history_timer_Int(void)
{
	__builtin_disable_interrupts();
	g_history = 0;
	g_print_time = 1;
	g_button_enable = 1;
	IFS0bits.T5IF = 0;
	__builtin_enable_interrupts();
}