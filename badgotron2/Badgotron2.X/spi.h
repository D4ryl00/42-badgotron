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

#define PIN_FLASH_MODE TRISAbits.TRISA0
#define PIN_FLASH_WRITE LATAbits.LATA0

#define PIN_RTC_MODE TRISAbits.TRISA7
#define PIN_RTC_WRITE LATAbits.LATA7

enum	e_spi_slave
{
	FLASH,
	RTC
};

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

