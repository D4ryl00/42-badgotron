#include "badgotron.h"

void	display_center_printstr(u8 *s, u8 len)
{
	u8	s_len;
	u8	diff;
	u8	i;
	u8	spaces;

	s_len = (u8)ft_strlen(s);
	if (s_len < len)
	{
		diff = len - s_len;
		spaces = diff / 2;
		i = -1;
		while (++i < spaces)
			display_printchar(' ');
		display_printstr(s);
		i = -1;
		spaces = diff % 2 ? spaces + 1 : spaces;
		while (++i < spaces)
			display_printchar(' ');
	}
	else
	{
	i = -1;
	while (++i < len)
		display_printchar(s[i]);
	}
}