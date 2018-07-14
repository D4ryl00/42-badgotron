#include "badgotron.h"

u8	daily_task(t_data_user *data)
{
	u8	is_modified;

	is_modified = 0;
	if (g_badger_mode)
	{
		if (data->timestamp)
		{
			data->timestamp = 0;
			is_modified = 1;
		}
	}
	else
	{
		if (data->timestamp)
		{
			db_update_user_out_time(data);
			is_modified = 1;
		}
	}
	if (data->current_day)
	{
		data->last_day = data->current_day;
		data->current_day = 0;
		is_modified = 1;
	}
	return (is_modified);
}

u8	weekly_task(t_data_user *data)
{
	u8	is_modified;

	is_modified = daily_task(data);
	if (data->current_week)
	{
		data->last_week = data->current_week;
		data->current_week = 0;
		is_modified = 1;
	}
	return (is_modified);
}

u8	monthly_task(t_data_user *data)
{
	u8	is_modified;

	is_modified = daily_task(data);
	/* test if it is also the end of the week */
	if (g_rtc_time.day == 0x01)
		is_modified |= weekly_task(data);
	if (data->current_month)
	{
		data->last_month = data->current_month;
		data->current_month = 0;
		is_modified = 1;
	}
	return (is_modified);
}

u8	trimesterly_task(t_data_user *data)
{
	u8	is_modified;

	is_modified = daily_task(data);
	/* test if it is also the end of the week */
	if (g_rtc_time.day == 0x01)
		is_modified |= weekly_task(data);
	/* test if it is also the end of the month */
	if (g_rtc_time.date == 0x01)
		is_modified |= monthly_task(data);
	if (data->current_trimester)
	{
		data->last_trimester = data->current_trimester;
		data->current_trimester = 0;
		is_modified = 1;
	}
	return (is_modified);
}