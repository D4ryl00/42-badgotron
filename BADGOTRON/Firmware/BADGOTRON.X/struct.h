/* 
 * File:   struct.h
 * Author: bocal
 *
 * Created on May 9, 2018, 3:40 PM
 */

#ifndef STRUCT_H
#define	STRUCT_H

#ifdef	__cplusplus
extern "C" {
#endif

union u_u8
{
    u8 allBits;
    struct
	{
		u8	bit0    :1;
		u8	bit1    :1;
		u8	bit2    :1;
		u8	bit3    :1;
		u8	bit4    :1;
		u8	bit5    :1;
		u8	bit6    :1;
		u8	bit7    :1;
    };
};

typedef struct  s_nanotime
{
	u16 nano;
	u16 micro;
	u16 milli;
	u8  second;
	u8  minute;
}               t_nanotime;

/*
** It's a BCD format:
** seconds = 10 SECONDS for 4 first bits + SECONDS for 4 last bits
** e.g. 18 seconds -> 0x18
*/
typedef struct	s_rtc_time
{
	u8	seconds;
	u8	minutes;
	u8	hour;
	u8	day;
	u8	date;
	u8	month;
	u8	year;
	u8	dst;
}				t_rtc_time;


/*index stuff from page */

typedef struct	__attribute__((packed))			s_index_user
{
	u8	id[5];
	u8	active;
}												t_index_user;

typedef struct	__attribute__((packed))			s_page_index
{
	t_index_user	user[682];
	u16		page_number;
}												t_page_index;


/*
** user stuff from page
*/
typedef struct	__attribute__((packed))			s_data_user
{
//u32	id;
	u32	timestamp;
	u16	current_day;
	u16	current_week;
	u16	current_month;
	u16	current_trimester;
	u16	last_day;
	u16	last_week;
	u16	last_month;
	u16	last_trimester;
	u16	sliding_days[7];
}												t_data_user;

typedef struct	__attribute__((packed))			s_page_data
{
	t_data_user		user[120]; // 120 * 34o = 4080o
	u16			page_number;
}												t_page_data;

/*
** Full page loaded from flash
*/
typedef union		u_flash_page
{
	u8		page[4096];
	t_page_index	index;
	t_page_data	data;
}					t_flash_page;

#ifdef	__cplusplus
}
#endif

#endif	/* STRUCT_H */

