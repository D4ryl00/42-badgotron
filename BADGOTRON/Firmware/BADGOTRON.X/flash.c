#include "badgotron.h"

void	flash_write_enable()
{
	spi_select_slave(FLASH);
	spi_put(FLASH_WRITE_ENABLE);
	spi_unselect_slave(FLASH);
}

static void	enable_write_status_register()
{
	spi_select_slave(FLASH);
	spi_put(FLASH_ENABLE_WRITE_STATUS_REGISTER);
	spi_unselect_slave(FLASH);
}

/* bpsbits0 for BP0
 * bpsbits1 for BP1
 * bpsbits2 for BP2
 */

static void write_status_register(u8 bps)
{
	spi_select_slave(FLASH);
	spi_put(FLASH_WRITE_STATUS_REGISTER);
	spi_put(bps);
	spi_unselect_slave(FLASH);
}

static void put_addr(u32 addr)
{
	spi_put(addr >> 16);
	spi_put((addr >> 8) & 0xff);
	spi_put(addr & 0xff);
}

u8		flash_get_id(void)
{
	u8	data;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_READ_ID, &data);
	spi_transfer(0, &data);
	spi_transfer(0, &data);
	spi_transfer(0, &data);
	spi_transfer(0, &data);
	spi_unselect_slave(FLASH);
	return (data);
}

u8		flash_get_status_register(void)
{
	u8	data;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_READ_STATUS_REGISTER, &data);
	spi_transfer(0, &data);
	spi_unselect_slave(FLASH);
	return (data);
}

void	flash_set_block_protection(u8 bps)
{
	__builtin_disable_interrupts();
	enable_write_status_register();
	write_status_register(0);
	__builtin_enable_interrupts();
}

void flash_put_byte(u32 addr, u8 data)
{
	flash_write_enable();
	spi_select_slave(FLASH);
	spi_put(FLASH_BYTE_PROGRAM);
	put_addr(addr);
	spi_put(data);
	spi_unselect_slave(FLASH);
}

u8	flash_get_byte(u32 addr)
{
	u8	data;

	spi_select_slave(FLASH);
	spi_put(FLASH_READ);
	put_addr(addr);
	data = spi_get();
	spi_unselect_slave(FLASH);
	return (data);
}