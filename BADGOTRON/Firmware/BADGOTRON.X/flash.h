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

#define FLASH_READ_ID 0x90
#define FLASH_ENABLE_WRITE_STATUS_REGISTER 0x50
#define FLASH_WRITE_ENABLE 0x06
#define	FLASH_READ_STATUS_REGISTER 0x05
#define FLASH_READ 0x03
#define FLASH_BYTE_PROGRAM 0x02
#define FLASH_WRITE_STATUS_REGISTER 0x01
#define FLASH_BP_SELECTION 0x00

#ifdef	__cplusplus
}
#endif

#endif	/* FLASH_H */

