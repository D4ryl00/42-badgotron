/* 
 * File:   rtc.h
 * Author: bocal
 *
 * Created on June 4, 2018, 5:10 PM
 */

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RTC_ID_READ 0x33
#define RTC_READ_STATUS_REGISTER 0x05
#define RTC_WRITE_ENABLE 0x06
#define RTC_WRITE_DISABLE 0x04
#define RTC_EEWRITE 0x02
#define RTC_EEREAD 0x03
#define RTC_WRITE 0x12
#define RTC_READ 0x13
#define RTC_SRWRITE 0x01

t_rtc_time g_rtc_time;

u8		rtc_get_status_register(void);
u8		rtc_eeread(u8 addr);
void	init_rtc(void);
void	rtc_update_time(void);
u8		rtc_oscillator_status(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

