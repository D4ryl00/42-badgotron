#include "badgotron.h"

static void	shift_sliding_days(t_data_user *data)
{
	u8	i;

	i = 7;
	while (--i)
		data->sliding_days[i] = data->sliding_days[i - 1];
	data->sliding_days[0] = 0;
}

void	daily_task(t_index_user *index, t_data_user *data, u8 is_parent)
{
	(void)index;
	(void)is_parent;
	if (g_badger_mode)
		data->timestamp = 0;
	else
	{
		if (data->timestamp)
			db_update_user_out_time(data);
	}
	shift_sliding_days(data);
	data->last_day = data->current_day;
	data->current_day = 0;
	rtc_eeputword(RTC_DAY_UPDATE_TS, get_timestamp());
}

void	weekly_task(t_index_user *index, t_data_user *data, u8 is_parent)
{
	(void)index;
	if (is_parent)
		daily_task(index, data, 0);
	data->last_week = data->current_week;
	data->current_week = 0;
	rtc_eeputword(RTC_WEEK_UPDATE_TS, get_timestamp());
}

void	monthly_task(t_index_user *index, t_data_user *data, u8 is_parent)
{
	(void)index;
	if (is_parent)
	{
		daily_task(index, data, 0);
		/* test if it is also the end of the week */
		if (g_rtc_time.day == 0x01)
			weekly_task(index, data, 0);
	}
	data->last_month = data->current_month;
	data->current_month = 0;
	rtc_eeputword(RTC_MONTH_UPDATE_TS, get_timestamp());
}

void	trimesterly_task(t_index_user *index, t_data_user *data, u8 is_parent)
{
	if (is_parent)
	{
		daily_task(index, data, 0);
		/* test if it is also the end of the week */
		if (g_rtc_time.day == 0x01)
			weekly_task(index, data, 0);
		/* test if it is also the end of the month */
		if (g_rtc_time.date == 0x01)
			monthly_task(index, data, 0);
	}
	if (!data->last_trimester && !data->current_trimester)
		index->inactive = 1;
	data->last_trimester = data->current_trimester;
	data->current_trimester = 0;
	rtc_eeputword(RTC_TRIMESTER_UPDATE_TS, get_timestamp());
}