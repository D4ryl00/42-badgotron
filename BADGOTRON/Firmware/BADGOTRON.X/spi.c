#include "badgotron.h"

void	init_spi(void)
{
	u32	rData;

	PIN_FLASH_MODE = 0;
	PIN_FLASH_WRITE = 1;

	/* Disable SPI interrupt */
	IEC1bits.SPI2EIE = 0;
	IEC1bits.SPI2RXIE = 0;
	IEC1bits.SPI2TXIE = 0;
	/* Stop SPI module */
	SPI2CONbits.ON = 0;
	/* Clearing the receive buffer */
	rData = SPI2BUF;
	/* Set Baud Rate = PBCLK / 2 */
	SPI2BRG = 31;
	/* clear the SPIROV bit */
	SPI2STATbits.SPIROV = 0;
	/* Set settings */
	/* Set Clock Edge */
	SPI2CONbits.CKE = 0;
	SPI2CONbits.CKP = 0;
	/* 8 bits communication */
	SPI2CONbits.MODE32 = 0;
	SPI2CONbits.MODE16 = 0;
	/* Master ON */
	SPI2CONbits.MSTEN = 1;
	/* Stop SPI module */
	SPI2CONbits.ON = 1;
}

void	spi_select_slave(enum e_spi_slave slave)
{
	if (slave == FLASH)
		PIN_FLASH_WRITE = SELECTED;
}

void	spi_unselect_slave(enum e_spi_slave slave)
{
	if (slave == FLASH)
		PIN_FLASH_WRITE = UNSELECTED;
}

void	spi_put(u8 code)
{
	while (SPI2STATbits.SPIBUSY);
	SPI2BUF = code;
}

void	spi_putstr(u8 *str, enum e_spi_slave slave)
{
	spi_select_slave(FLASH);
	while (*str)
	{
		while (SPI2STATbits.SPIBUSY);
		SPI2BUF = *str++;
	}
	spi_unselect_slave(FLASH);
}

u8		spi_get(void)
{
	while (!SPI2STATbits.SPIRBF);
	return (SPI2BUF);
}