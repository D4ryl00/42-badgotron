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

#define RTC_PIN_MFP_MODE TRISAbits.TRISA10
#define RTC_PIN_MFP_READ PORTAbits.RA10
#define RTC_PIN_MFP_CN CNENAbits.CNIEA10
#define RTC_PIN_MFP_PULLUP CNPUAbits.CNPUA10

#define RTC_TRIMESTER_UPDATE_TS 0
#define RTC_MONTH_UPDATE_TS 4
#define RTC_WEEK_UPDATE_TS 8
#define RTC_DAY_UPDATE_TS 12
#define RTC_LAST_TIMESTAMP 16

t_rtc_time g_rtc_time;

u8		rtc_get_status_register(void);
u8		rtc_eeread(u8 addr);
void	init_rtc(u8 init, u8 test, u8 sync);
void	rtc_update_time(void);
u8		rtc_oscillator_status(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

