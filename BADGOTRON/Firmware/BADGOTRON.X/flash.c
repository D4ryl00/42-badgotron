#include "badgotron.h"

static void	enable_write_status_register()
{
	spi_select_slave(FLASH);
	spi_put(ENABLE_WRITE_STATUS_REGISTER);
	spi_unselect_slave(FLASH);
}

static void	write_enable()
{
	spi_select_slave(FLASH);
	spi_put(FLASH_WRITE_ENABLE);
	spi_unselect_slave(FLASH);
}

void	flash_instruction(u8 code)
{
	spi_select_slave(FLASH);
	spi_put(code);
	spi_unselect_slave(FLASH);
}

/* bpsbits0 for BP0
 * bpsbits1 for BP1
 * bpsbits2 for BP2
 */

static void write_status_register(u8 bps)
{
	spi_select_slave(FLASH);
	spi_put(WRITE_STATUS_REGISTER);
	spi_put(bps);
	spi_unselect_slave(FLASH);
}

static void	disable_block_protection(u8 bps)
{
	__builtin_disable_interrupts();
	enable_write_status_register();
	write_status_register(0);
	__builtin_enable_interrupts();
}

static void flash_put_addr(u32 addr)
{
	spi_put(addr >> 16);
	spi_put((addr >> 8) & 0xff);
	spi_put(addr & 0xff);
}

static void byte_program(u32 addr, u8 data)
{
	write_enable();
	spi_select_slave(FLASH);
	spi_put(BYTE_PROGRAM);
	flash_put_addr(addr);
	spi_put(data);
	spi_unselect_slave(FLASH);
}