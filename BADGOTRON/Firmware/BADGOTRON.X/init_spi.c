#include "badgotron.h"

void	init_spi(void)
{
	u32	rData;

	/* Disable SPI interrupt */
	IEC1bits.SPI2EIE = 0;
	IEC1bits.SPI2RXIE
	IEC1bits.SPI2TXIE = 0;
	/* Stop SPI module */
	SPI2CONbits.ON = 0;
	/* Clearing the receive buffer */
	rData = SPI2BUF;
	/* Set Baud Rate = PBCLK / 2 */
	SPI2BRG = 0;
	/* clear the SPIROV bit */
	SPI2STATbits.SPIROV = 0;
	/* Set settings */
	/* 32 bits communication */
	SPI2CONbits.MODE32 = 1;
	/* Master ON */
	SPI2CONbits.MSTEN = 1;
	/* Stop SPI module */
	SPI2CONbits.ON = 1;
}