#include "badgotron.h"

void		show_history(void)
{
	u8			id[5];
	u8			checksum;
	u32			minutes_today = 0;
	t_data_user	*data_user;

	g_button_enable = 2;
	if (!(checksum = checksum_is_ok()))
	{
		display_clear();
		display_printstr("Erreur de lecture du badge.");
		msleep(2000);
		display_clear();
		return ;
	}
	display_clear();
	convert_format_id(id, g_wiegand_buf.buffer);
	if (!(data_user = get_data_user(id, checksum)))
		display_printstr("ID inconnu.");
	else
	{
		if (data_user->timestamp)
			minutes_today = ((get_timestamp() - data_user->timestamp) / 60);
		minutes_today += data_user->current_day;
		display_printstr("Aujourd'hui ");
		print_hours(minutes_today, 3, 2);
		display_printstr("Mois      ");
		print_hours(minutes_today + data_user->current_month, 3, 4);
		display_printstr("Semaine    ");
		print_hours(minutes_today + data_user->current_week, 3, 3);
		display_printstr("Trimestre ");
		print_hours(minutes_today + data_user->current_trimester, 3, 4);
	}
	history_timer_init();
	g_print_enable = 0;
}

void		show_history_pagetwo(void)
{
	u8			id[5];
	u8			checksum;
	t_data_user	*data_user;

	g_print_enable = 1;
	if (!(checksum = checksum_is_ok()))
	{
		display_clear();
		display_printstr("Erreur de lecture du badge.");
		msleep(2000);
		display_clear();
		return ;
	}
	display_clear();
	convert_format_id(id, g_wiegand_buf.buffer);
	if (!(data_user = get_data_user(id, checksum)))
		display_printstr("ID inconnu.");
	else
	{
		display_printstr("Hier        ");
		print_hours(data_user->last_day, 3, 2);
		display_printstr("Mois -1   ");
		print_hours(data_user->last_month, 3, 4);
		display_printstr("Semaine -1 ");
		print_hours(data_user->last_week, 3, 3);
		display_printstr("Trimes. -1");
		print_hours(data_user->last_trimester, 3, 4);
	}
	g_print_enable = 0;
}