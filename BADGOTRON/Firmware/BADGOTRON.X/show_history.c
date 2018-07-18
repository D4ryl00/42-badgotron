#include "badgotron.h"

static void	print_hours(u32 minutes, u8 padding)
{
	u8 digits = 1;
	u32 hours = minutes / 60;

	display_printstr("   ");
	while (hours >= 10)
	{
		hours /= 10;
		digits++;
	}
	while (digits < padding)
	{
		display_printstr(" ");
		digits++;
	}
	putnbr(minutes / 60);
	display_printstr("h");
	if (minutes % 60 % 10 == 0)
		display_printchar('0');
	putnbr(minutes % 60);
}

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
		print_hours(minutes_today, 2);
		display_printstr("Mois      ");
		print_hours(minutes_today + data_user->current_month, 4);
		display_printstr("Semaine    ");
		print_hours(minutes_today + data_user->current_week, 3);
		display_printstr("Trimestre ");
		print_hours(minutes_today + data_user->current_trimester, 4);
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
		print_hours(data_user->last_day, 2);
		display_printstr("Mois -1   ");
		print_hours(data_user->last_month, 4);
		display_printstr("Semaine -1 ");
		print_hours(data_user->last_week, 3);
		display_printstr("Trimes. -1");
		print_hours(data_user->last_trimester, 4);
	}
	g_print_enable = 0;
}
