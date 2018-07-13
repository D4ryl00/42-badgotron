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
	return (is_modified);
}

void	weekly_task(void)
{
}

void	monthly_task(void)
{
}

void	trimesterly_task(void)
{
}