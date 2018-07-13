#include "badgotron.h"

void	conv_rasp_time(void)
{
	g_rtc_time.seconds = 0x45;
	g_rtc_time.minutes = 0x59;
	g_rtc_time.hour = 0x14;
	g_rtc_time.day = 0x05;
	g_rtc_time.date = 0x13;
	g_rtc_time.month = 0x07;
	g_rtc_time.year = 0x18;
	g_rtc_time.dst = 1;
	// seconds
	/*g_rtc_time.seconds = 0;
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

	while (g_uart_rx_buf.index < 2)
	{
		uart_putstr("time_dst?\n");
		while (!g_uart_rx_buf.index);
		if (g_uart_rx_buf.index < 2)
			uart_clear_buffer();
	}
	g_rtc_time.dst = g_uart_rx_buf.buffer[1] - '0';*/
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

u32	get_timestamp()
{
	t_rtc_time	time;
	u32			timestamp;
	u8			calendar [] = {31, 28, 31, 30
					,31, 30, 31, 31
					,30, 31, 30, 31};

	//convert date from bcd format to decimal
	time.year = ((g_rtc_time.year >> 4) * 10) + (g_rtc_time.year & 0x0f);
	time.month = ((g_rtc_time.month >> 4) * 10) + (g_rtc_time.month & 0x0f);
	time.date = ((g_rtc_time.date >> 4) * 10) + (g_rtc_time.date & 0x0f);
	time.hour = ((g_rtc_time.hour >> 4) * 10) + (g_rtc_time.hour & 0x0f);
	time.minutes = ((g_rtc_time.minutes >> 4) * 10) + (g_rtc_time.minutes & 0x0f);
	time.seconds = ((g_rtc_time.seconds >> 4) * 10) + (g_rtc_time.seconds & 0x0f);
	timestamp = 0;
	if ((!((time.year + 2000) % 4)) && (time.month > 2))
		timestamp += 86400; // if the current year is a leap one -> add one day (86400 sec)
	while (time.month > 1) // sum the days from January to the current month
	{
		time.month--; // dec the month
		timestamp += (calendar[time.month]) * 86400 ; // add the number of days from a month * 86400 sec
	}
	timestamp += ((time.year + 30) / 4) * (3600 * 24);
	timestamp += (time.year + 30) * (3600*24*365);
	timestamp += (time.date - 1) * (3600 * 24);
	timestamp += time.hour * 3600;
	timestamp += time.minutes * 60;
	timestamp += time.seconds;
	if (g_rtc_time.dst)
		timestamp -= 3600 * 2;
	else
		timestamp -= 3600;
	return (timestamp);
}