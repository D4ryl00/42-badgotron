#include "badgotron.h"

static u8	get_status_register(void)
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_READ_STATUS_REGISTER, &data);
	spi_transfer(0, &data);
	spi_unselect_slave(FLASH);
	return (data);
}

static u8	busy(void)
{
	return (get_status_register() & 0x01);
}

static u8	hw_busy(void)
{
	u8	status;

	spi_select_slave(FLASH);
	status = FLASH_PIN_SO;
	spi_unselect_slave(FLASH);
	return (!status);
}

static void	write_enable()
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_WRITE_ENABLE, &data);
	spi_unselect_slave(FLASH);
}

static void	write_disable()
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_WRITE_DISABLE, &data);
	spi_unselect_slave(FLASH);
}

static void	enable_write_status_register()
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_ENABLE_WRITE_STATUS_REGISTER, &data);
	spi_unselect_slave(FLASH);
}

static void write_status_register(u8 code)
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_WRITE_STATUS_REGISTER, &data);
	spi_transfer(code, &data);
	spi_unselect_slave(FLASH);
	while(busy());
}

static void put_addr(u32 addr)
{
	u8	data = 0;

	spi_transfer(addr >> 16, &data);
	spi_transfer((addr >> 8) & 0xff, &data);
	spi_transfer(addr & 0xff, &data);
}

static void	enable_hw_eow_detection(void)
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_EBSY, &data);
	spi_unselect_slave(FLASH);
}

static void	disable_hw_eow_detection(void)
{
	u8	data = 0;

	spi_select_slave(FLASH);
	spi_transfer(FLASH_DBSY, &data);
	spi_unselect_slave(FLASH);
}

u8		flash_get_id(void)
{
	u8	data;

	__builtin_disable_interrupts();
	spi_select_slave(FLASH);
	spi_transfer(FLASH_READ_ID, &data);
	put_addr(0);
	spi_transfer(0, &data);
	spi_unselect_slave(FLASH);
	__builtin_enable_interrupts();
	return (data);
}

void	flash_set_block_protection(u8 code)
{
	__builtin_disable_interrupts();
	enable_write_status_register();
	write_status_register(code);
	__builtin_enable_interrupts();
}

void	flash_4k_erase(u32 addr)
{
	u8	data = 0;

	__builtin_disable_interrupts();
	write_enable();
	spi_select_slave(FLASH);
	spi_transfer(FLASH_4K_ERASE, &data);
	put_addr(addr);
	spi_unselect_slave(FLASH);
	__builtin_enable_interrupts();
	while(busy());
}

void	flash_write(u32 addr, u8 data)
{
	u8	tmp = 0;

	__builtin_disable_interrupts();
	write_enable();
	spi_select_slave(FLASH);
	spi_transfer(FLASH_BYTE_PROGRAM, &tmp);
	put_addr(addr);
	spi_transfer(data, &tmp);
	spi_unselect_slave(FLASH);
	__builtin_enable_interrupts();
	while(busy());
}

void		flash_put_byte(u32 addr, u8 data)
{
	flash_set_block_protection(FLASH_BLOCK_UNPROTECTED);
	flash_4k_erase(addr);
	flash_write(addr, data);
	flash_set_block_protection(FLASH_BLOCK_PROTECTED);
}

u8			flash_get_byte_init(u32 addr)
{
	u8	data = 0;

	__builtin_disable_interrupts();
	spi_select_slave(FLASH);
	spi_transfer(FLASH_READ, &data);
	put_addr(addr);
	spi_transfer(0, &data);
	return (data);
}

u8			flash_get_byte_next(void)
{
	u8	data = 0;
	spi_transfer(0, &data);
	return (data);
}

u8			flash_get_byte_end(void)
{
	spi_unselect_slave(FLASH);
	__builtin_enable_interrupts();
}

void		flash_put_multibytes(u32 addr, u8 *data, u16 size)
{
	u8	tmp = 0;
	u16	i = 0;

	if (size < 2)
		return ;
	flash_set_block_protection(FLASH_BLOCK_UNPROTECTED);
	display_printchar('Y');
	flash_4k_erase(addr);
	__builtin_disable_interrupts();
	enable_hw_eow_detection();
	write_enable();
	/* Send the first two bytes */
	spi_select_slave(FLASH);
	spi_transfer(FLASH_AAI, &tmp);
	put_addr(addr);
	spi_transfer(data[i++], &tmp);
	spi_transfer(data[i++], &tmp);
	spi_unselect_slave(FLASH);
	while(hw_busy());
	/* Send other bytes */
	while (i < size)
	{
		spi_select_slave(FLASH);
		spi_transfer(FLASH_AAI, &tmp);
		spi_transfer(data[i++], &tmp);
		spi_transfer(i == size ? 0 : data[i++], &tmp);
		spi_unselect_slave(FLASH);
		while(hw_busy());
	}
	/* Initialize end of protocol */
	write_disable();
	disable_hw_eow_detection();
	__builtin_enable_interrupts();
	flash_set_block_protection(FLASH_BLOCK_PROTECTED);
}