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

#define FLASH_WRITE_ENABLE 0x06
#define ENABLE_WRITE_STATUS_REGISTER 0x50
#define BYTE_PROGRAM 0x02
#define WRITE_STATUS_REGISTER 0x01
#define FLASH_BP_SELECTION 0x00

#ifdef	__cplusplus
}
#endif

#endif	/* FLASH_H */

