#include "badgotron.h"

static u8	is_id_equ(u8 *id1, u8 *id2)
{
	u8	i;

	i = -1;
	while (++i < 5)
	{
		if (id1[i] != id2[i])
			return (0);
	}
	return (1);
}

static u8	is_id_null(u8 *id1)
{
	u8	i;

	i = -1;
	while (++i < 5)
	{
		if (id1[i] != 0)
			return (0);
	}
	return (1);
}

static void	id_cpy(u8 *dest, u8 *src)
{
	u8	i;

	i = -1;
	while (++i < 5)
		dest[i] = src[i];
}

void	db_adduser(u8 *id)
{
	u8	page = -1;
	u8	user;

	while (++page < 47)
	{
		user = -1;
		while (++user < 682)
		{
			if (is_id_null(g_db_index[user].id))
			{
				id_cpy(g_db_index[user].id, id);
				g_db_index[user].active = 1;
				return ;
			}
		}
	}
}