#include "badgotron.h"

static	u8 busy(void)
{
	u8	busy;

	busy = rtc_get_status_register();
	return (busy & 0x01);
}

static void write_enable(void)
{
	u8	tmp = 0;

	spi_select_slave(RTC);
	spi_transfer(RTC_WRITE_ENABLE, &tmp);
	spi_unselect_slave(RTC);
	while (busy());
}

static void write_disable(void)
{
	u8	tmp = 0;

	spi_select_slave(RTC);
	spi_transfer(RTC_WRITE_DISABLE, &tmp);
	spi_unselect_slave(RTC);
	while (busy());
}

void rtc_eewrite(u8 addr, u8 data)
{
	u8	tmp = 0;

	__builtin_disable_interrupts();
	write_enable();
	spi_select_slave(RTC);
	spi_transfer(RTC_EEWRITE, &tmp);
	spi_transfer(addr, &tmp);
	spi_transfer(data, &tmp);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
	while (busy());
}

u8	rtc_eeread(u8 addr)
{
	u8	data = 0;

	__builtin_disable_interrupts();
	spi_select_slave(RTC);
	spi_transfer(RTC_EEREAD, &data);
	spi_transfer(addr, &data);
	spi_transfer(0, &data);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
	return (data);
}

static void	write_byte(u8 addr, u8 data)
{
	u8	tmp = 0;

	spi_select_slave(RTC);
	spi_transfer(RTC_WRITE, &tmp);
	spi_transfer(addr, &tmp);
	spi_transfer(data, &tmp);
	spi_unselect_slave(RTC);
	while (busy());
}

static u8	read_byte(u8 addr)
{
	u8	data = 0;

	spi_select_slave(RTC);
	spi_transfer(RTC_READ, &data);
	spi_transfer(addr, &data);
	spi_transfer(0, &data);
	spi_unselect_slave(RTC);
	return (data);
}

void	rtc_srwrite(u8 data)
{
	u8	tmp = 0;

	__builtin_disable_interrupts();
	spi_select_slave(RTC);
	spi_transfer(RTC_SRWRITE, &tmp);
	spi_transfer(data, &tmp);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
	while (busy());
}

void init_rtc(t_rtc_time time)
{
	u8 tmp;

	// hundredths of seconds
	write_byte(0x00, 0x00);
	// seconds
	write_byte(0x01, 0x80 | time.seconds);
	// minutes
	write_byte(0x02, time.minutes);
	// hour = CALSGN + 12/24=0 + 10 HOUR + 10 HOUR + HOUR
	write_byte(0x03, 0x3F & time.hour);
	// day = - - - VBAT=1 VBATEN=0 DAY
	//write_byte(0x04, 0x17 & time.day);
	// date = - - 10 DATE + DATE
	write_byte(0x05, 0x3F & time.date);
	// month = LP + 10 MONTH + MONTH
	write_byte(0x06, 0x1F & time.month);
	// year = 10 YEAR + YEAR
	write_byte(0x07, time.year);
	// Configuration bits
	write_byte(0x08, 0x00);
	// Calibration
	write_byte(0x09, 0x00);
}

u8  rtc_get_id(void)
{
	u8	data = 0;
	u8	addr = 0;

	__builtin_disable_interrupts();
	spi_select_slave(RTC);
	spi_transfer(RTC_ID_READ, &data);
	spi_transfer(addr, &data);
	spi_transfer(0x00, &data);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
	return (data);
}

u8  rtc_get_status_register(void)
{
	u8	data = 0;

	__builtin_disable_interrupts();
	spi_select_slave(RTC);
	spi_transfer(RTC_READ_STATUS_REGISTER, &data);
	spi_transfer(0, &data);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
	return (data);
}

void	rtc_update_time(void)
{
	__builtin_disable_interrupts();
	g_rtc_time.seconds = read_byte(0x01) & 0xef;
	g_rtc_time.minutes = read_byte(0x02) & 0xef;
	g_rtc_time.hour = read_byte(0x03) & 0x3f;
	g_rtc_time.date = read_byte(0x05) & 0x3f;
	g_rtc_time.month = read_byte(0x06) & 0x1f;
	g_rtc_time.year = read_byte(0x07);
}

u8	rtc_oscillator_status(void)
{
	return (read_byte(0x05) & 0x20);
}