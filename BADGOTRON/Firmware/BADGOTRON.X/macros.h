/* 
 * File:   macros.h
 * Author: bocal
 *
 * Created on May 9, 2018, 5:02 PM
 */

#ifndef MACROS_H
#define	MACROS_H

#ifdef	__cplusplus
//extern "C" {
#endif

#define DISPLAY_DELAY 8
#define DISPLAY_DELAY2 15
#define PBCLK 40000000

#define PIN_MODE_OUTPUT 0
#define PIN_MODE_INPUT 1

#define FLASH_PAGE_SIZE 4096
#define FLASH_INDEX_PAGE_PER_CHECKSUM 2
#define FLASH_INDEX_USER_PER_PAGE 682
#define FLASH_INDEX_USER_PAGE_SIZE 4092
#define FLASH_INDEX_PAGE_NBR 32
#define FLASH_DATA_USER_SIZE 38
#define FLASH_DATA_USER_PER_PAGE 107

#ifdef	__cplusplus
}
#endif

#endif	/* MACROS_H */

