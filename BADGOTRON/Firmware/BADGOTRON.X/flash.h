/* 
 * File:   flash.h
 * Author: bocal
 *
 * Created on May 31, 2018, 10:47 AM
 */

#ifndef FLASH_H
#define	FLASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FLASH_PIN_SO PORTGbits.RG7

#define FLASH_BLOCK_UNPROTECTED 0
#define FLASH_BLOCK_PROTECTED 0b10111100
#define FLASH_AAI 0xAD
//#define FLASH_READ_ID 0x90
#define FLASH_READ_ID 0xAB
#define	FLASH_CHIPERASE 0x60
#define FLASH_DBSY 0x80
#define FLASH_EBSY 0x70
#define FLASH_ENABLE_WRITE_STATUS_REGISTER 0x50
#define FLASH_4K_ERASE 0x20
#define FLASH_WRITE_ENABLE 0x06
#define	FLASH_READ_STATUS_REGISTER 0x05
#define FLASH_WRITE_DISABLE 0x04
#define FLASH_READ 0x03
#define FLASH_BYTE_PROGRAM 0x02
#define FLASH_WRITE_STATUS_REGISTER 0x01
#define FLASH_BP_SELECTION 0x00

u8		flash_get_id(void);
void	flash_set_block_protection(u8 code);
void	flash_4k_erase(u32 addr);
void	flash_write(u32 addr, u8 data);
void	flash_put_byte(u32 addr, u8 data);
u8		flash_get_byte_init(u32 addr);
u8		flash_get_byte_next(void);
u8		flash_get_byte_end(void);
void	flash_chiperase(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FLASH_H */

