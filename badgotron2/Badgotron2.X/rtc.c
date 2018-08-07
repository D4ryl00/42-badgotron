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

void	rtc_eeputword(u8 addr, u32 data)
{
	u8	tmp = 0;
	u8	*p = (u8 *)&data;
	u8	i = -1;

	__builtin_disable_interrupts();
	write_enable();
	spi_select_slave(RTC);
	spi_transfer(RTC_EEWRITE, &tmp);
	spi_transfer(addr, &tmp);
	while (++i < 4)
		spi_transfer(p[i], &tmp);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
	while (busy());
}

u32	rtc_eereadword(u8 addr)
{
	u32	data = 0;
	u8	i = -1;
	u8	*p = (u8 *)&data;

	__builtin_disable_interrupts();
	spi_select_slave(RTC);
	spi_transfer(RTC_EEREAD, &data);
	spi_transfer(addr, &data);
	while (++i < 4)
		spi_transfer(0,	p + i);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
	return (data);
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

	__builtin_disable_interrupts();
	spi_select_slave(RTC);
	spi_transfer(RTC_WRITE, &tmp);
	spi_transfer(addr, &tmp);
	spi_transfer(data, &tmp);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
}

static u8	read_byte(u8 addr)
{
	u8	data = 0;

	__builtin_disable_interrupts();
	spi_select_slave(RTC);
	spi_transfer(RTC_READ, &data);
	spi_transfer(addr, &data);
	spi_transfer(0, &data);
	spi_unselect_slave(RTC);
	__builtin_enable_interrupts();
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

static u8	is_on_time()
{
	return (read_byte(0x01) & 0x80);
}

void	rtc_set_time(void)
{
	// Disable Oscillator and wait
	write_byte(0x01, 0x00);
	while (read_byte(0x04) & 0x20);
	// day = VBAT=0 VBATEN=1 DAY
	write_byte(0x04, 0x08 | (g_rtc_time.day & 0x07));

	// Settting time
	// year = 10 YEAR + YEAR
	write_byte(0x07, g_rtc_time.year);
	// month = LP + 10 MONTH + MONTH
	write_byte(0x06, g_rtc_time.month);
	// date = - - 10 DATE + DATE
	write_byte(0x05, g_rtc_time.date);
	// hour = CALSGN + 12/24=0 + 0 + 10 HOUR + HOUR
	write_byte(0x03, g_rtc_time.hour);
	// minutes
	write_byte(0x02, g_rtc_time.minutes);
	// seconds
	write_byte(0x01, 0x80 | g_rtc_time.seconds);
	// DST value (Summer time)
	write_byte(0x20, g_rtc_time.dst);
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
	g_rtc_time.year = read_byte(0x07);
	g_rtc_time.month = read_byte(0x06) & 0x1f;
	g_rtc_time.date = read_byte(0x05);
	g_rtc_time.hour = read_byte(0x03);
	g_rtc_time.minutes = read_byte(0x02);
	g_rtc_time.seconds = read_byte(0x01) & 0x7f;
	g_rtc_time.day = read_byte(0x04) & 0x07;
	g_rtc_time.dst = read_byte(0x20);
}

u8	rtc_oscillator_status(void)
{
	return ((read_byte(0x01) & 0x80) | (read_byte(0x04) & 0x20));
	//return ((read_byte(0x04) & 0x20));
	//return (read_byte(0x01) & 0x80);
}

void init_rtc(u8 test)
{
	u8	tmp;

	// Init pin for alarms
	__builtin_disable_interrupts(); // Desativer les interrupts partout
	RTC_PIN_MFP_MODE = PIN_MODE_INPUT;
	RTC_PIN_MFP_CN = 1;
	RTC_PIN_MFP_PULLUP = 1;
	CNCONAbits.ON = 1; //Enable CON (CN interrupts)
	// READ PORT BIT FOR CLEARING IT
	tmp = RTC_PIN_MFP_READ;
	// INTERRUPT
	IPC8bits.CNIP = 7;
	IPC8bits.CNIS = 3;
	IFS1bits.CNAIF = 0;
	IEC1bits.CNAIE = 1;
	__builtin_enable_interrupts();
	// Set alarms
	write_byte(0x0d, 0x00);
	// Set day and alarm match
	write_byte(0x0f, 0x10);
	// End of init alarms
	// Configuration bits
	write_byte(0x08, 0x10);
	// Calibration
	write_byte(0x09, 0x00);
	if (!is_on_time() || test)
	{
		conv_rasp_time(test);
		rtc_set_time();
	}
}

void	rtc_disable_alarm_flag(void)
{
	u8	config;

	config = read_byte(0x0f) & (~0x08);
	write_byte(0x0f, config);
}