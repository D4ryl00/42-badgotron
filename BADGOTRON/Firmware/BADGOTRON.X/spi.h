/* 
 * File:   spi.h
 * Author: bocal
 *
 * Created on May 31, 2018, 8:33 AM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SELECTED 0
#define UNSELECTED 1

#define PIN_FLASH_MODE TRISEbits.TRISE0
#define PIN_FLASH_WRITE LATEbits.LATE0

#define PIN_RTC_MODE TRISEbits.TRISE1
#define PIN_RTC_WRITE LATEbits.LATE1

enum	e_spi_slave
{
	FLASH,
	RTC
};

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

