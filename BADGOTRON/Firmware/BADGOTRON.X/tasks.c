#include "badgotron.h"

void	daily_task(t_data_user *data)
{
	if (g_badger_mode)
	{
		data->timestamp = 0;
	}
	else
	{
		if (data->timestamp)
			db_update_user_out_time(data);
	}
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