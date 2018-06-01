#include "badgotron.h"

void	flash_write_enable()
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_WRITE_ENABLE, &data);
	spi_unselect_slave(FLASH);
}

static void	enable_write_status_register()
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_ENABLE_WRITE_STATUS_REGISTER, &data);
	spi_unselect_slave(FLASH);
}

/* bpsbits0 for BP0
 * bpsbits1 for BP1
 * bpsbits2 for BP2
 */

static void write_status_register(u8 bps)
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_WRITE_STATUS_REGISTER, &data);
	spi_transfer(bps, &data);
	spi_unselect_slave(FLASH);
}

static void put_addr(u32 addr)
{
	u8	data = 0;

	spi_transfer(addr >> 16, &data);
	spi_transfer((addr >> 8) & 0xff, &data);
	spi_transfer(addr & 0xff, &data);
}

u8		flash_get_id(void)
{
	u8	data;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_READ_ID, &data);
	put_addr(0);
	spi_transfer(0, &data);
	spi_unselect_slave(FLASH);
	return (data);
}

u8		flash_get_status_register(void)
{
	u8	data = 0;

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

static u8	is_busy(void)
{
	return (flash_get_status_register() & 0x01);
}

void flash_4k_erase(u32 addr)
{
	u8	data = 0;

	flash_write_enable();
	spi_select_slave(FLASH);
	spi_transfer(FLASH_4K_ERASE, &data);
	put_addr(addr);
	spi_unselect_slave(FLASH);
	while(is_busy());
}

void flash_put_byte(u32 addr, u8 data)
{
	u8	tmp = 0;

	flash_write_enable();
	spi_select_slave(FLASH);
	spi_transfer(FLASH_BYTE_PROGRAM, &tmp);
	put_addr(addr);
	spi_transfer(data, &tmp);
	spi_unselect_slave(FLASH);
	while(is_busy());
}

u8	flash_get_byte(u32 addr)
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_READ, &data);
	put_addr(addr);
	spi_transfer(0, &data);
	spi_unselect_slave(FLASH);
	return (data);
}