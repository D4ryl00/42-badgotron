#include "types.h"
#include "struct.h"
#include "macros.h"
#include <p32xxxx.h>
#include <xc.h>

/*static void write_enable_rtc()
{
	u8 tmp = 0;
	spi_select_slave(RTC);
	spi_transfer(0x06, &tmp);
	spi_unselect_slave(RTC);
}

static void eewrite_rtc(u8 addr, u8 data)
{
	u8 tmp;
	//peut etre optimise
	spi_select_slave(RTC);
	spi_transfer(0x02, &tmp);
	spi_transfer(addr, &tmp);
	spi_transfer(data, &tmp);
	spi_unselect_slave(RTC);
}

static void get_time(

static void init_rtc()
{
	u8 tmp;
	//peut etre optimise
	eewrite_rtc(0x00, 0x00);
	eewrite_rtc(0x01, 0x00); //seconde = 0
	eewrite_rtc(0x02, 0x00); // minutes = 0
	eewrite_rtc(0x03, 0x9F); // Mode 24 heures - heures set a 18;
	eewrite_rtc(0x04, 0x06); // Jour 6 de la semaine
	eewrite_rtc(0x05, 0x06); // Jour 6 du mois;
	eewrite_rtc(0x06, 0x06); // Mois 6
	eewrite_rtc(0x07, 0x1F); // Annee 2018
	eewrite_rtc(0x08, 0x00); // Configuration bits
	eewrite_rtc(0x09, 0x00); // calibration  (a voir)
}

static void init_rtc()
{
	write_enable_rtc();
	init_rtc();
}
*/