#include "badgotron.h"

void	conv_rasp_time(void)
{
	/*g_rtc_time.seconds = 0x25;
	g_rtc_time.minutes = 0x39;
	g_rtc_time.hour = 0x10;
	g_rtc_time.day = 0x04;
	g_rtc_time.date = 0x07;
	g_rtc_time.month = 0x06;
	g_rtc_time.year = 0x18;*/
	// seconds
	g_rtc_time.seconds = 0;
	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_second?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.seconds = g_uart_rx_buf.buffer[1] - '0';
	g_rtc_time.seconds += (g_uart_rx_buf.buffer[0] - '0') << 4;
	uart_clear_buffer();

	// minutes
	g_rtc_time.minutes = 0;
	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_minute?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.minutes = g_uart_rx_buf.buffer[1] - '0';
	g_rtc_time.minutes += (g_uart_rx_buf.buffer[0] - '0') << 4;
	uart_clear_buffer();

	// hours
	g_rtc_time.hour = 0;
	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_hour?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.hour = g_uart_rx_buf.buffer[1] - '0';
	g_rtc_time.hour += (g_uart_rx_buf.buffer[0] - '0') << 4;
	uart_clear_buffer();

	// day
	g_rtc_time.day = 0;
	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_wday?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.day = g_uart_rx_buf.buffer[1] - '0';
	g_rtc_time.day += (g_uart_rx_buf.buffer[0] - '0') << 4;
	uart_clear_buffer();

	// date
	g_rtc_time.date = 0;
	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_day?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.date = g_uart_rx_buf.buffer[1] - '0';
	g_rtc_time.date += (g_uart_rx_buf.buffer[0] - '0') << 4;
	uart_clear_buffer();

	// month
	g_rtc_time.month = 0;
	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_month?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.month = g_uart_rx_buf.buffer[1] - '0';
	g_rtc_time.month += (g_uart_rx_buf.buffer[0] - '0') << 4;
	uart_clear_buffer();

	// year
	g_rtc_time.year = 0;
	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_year?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.year = g_uart_rx_buf.buffer[1] - '0';
	g_rtc_time.year += (g_uart_rx_buf.buffer[0] - '0') << 4;
	uart_clear_buffer();
}

void	print_time(void)
{
	display_printchar((g_rtc_time.day >> 4) + '0');
	display_printchar((g_rtc_time.day & 0x0f) + '0');
	display_printstr(" ");
	display_printchar((g_rtc_time.date >> 4) + '0');
	display_printchar((g_rtc_time.date & 0x0f) + '0');
	display_printstr("/");
	display_printchar((g_rtc_time.month >> 4) + '0');
	display_printchar((g_rtc_time.month & 0x0f) + '0');
	display_printstr("/");
	display_printchar((g_rtc_time.year >> 4) + '0');
	display_printchar((g_rtc_time.year & 0x0f) + '0');
	display_printstr(" ");
	display_printchar((g_rtc_time.hour >> 4) + '0');
	display_printchar((g_rtc_time.hour & 0x0f) + '0');
	display_printstr(":");
	display_printchar((g_rtc_time.minutes >> 4) + '0');
	display_printchar((g_rtc_time.minutes & 0x0f) + '0');
	display_printstr(":");
	display_printchar((g_rtc_time.seconds >> 4) + '0');
	display_printchar((g_rtc_time.seconds & 0x0f) + '0');
}