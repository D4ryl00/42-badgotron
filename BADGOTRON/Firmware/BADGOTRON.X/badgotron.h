/* 
 * File:   badgotron.h
 * Author: bocal
 *
 * Created on May 17, 2018, 11:44 AM
 */

#ifndef BADGOTRON_H
#define	BADGOTRON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
#include "types.h"
#include "struct.h"
#include "prototypes.h"
#include "macros.h"
#include "uart.h"
#include "spi.h"
#include "flash.h"
#include "rtc.h"
#include "badge.h"
#include "button.h"
#include "NRJ.h"

/* Display */
#include "display_pin_select.h"
/*SERVO*/
#include "servo.h"

extern u8				g_display_str[80];
extern u8				g_print_enable;
extern t_flash_page		g_flash_index;
extern t_flash_page		g_flash_data;
extern t_wiegand_buf	g_wiegand_buf;
extern u8				g_badger_mode;
extern u8				g_history;
extern u8				g_button_enable;

#ifdef	__cplusplus
}
#endif

#endif	/* BADGOTRON_H */

