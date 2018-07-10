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

void	id_cpy(u8 *dest, u8 *src)
{
	u8	i;

	i = -1;
	while (++i < 5)
		dest[i] = src[i];
}

s16		get_first_free_space(u8 checksum)
{
	u16	offset;
	u16	position;
	u16 pageslues;

	g_flash_index.index.page_number = FLASH_INDEX_PAGE_PER_CHECKSUM * checksum - 1;
	pageslues = -1;
	while (++pageslues < FLASH_INDEX_PAGE_MAX)
	{
		offset = 0;
		g_flash_index.index.page_number++;
		g_flash_index.page[0] = flash_get_byte_init(g_flash_index.index.page_number * FLASH_PAGE_SIZE);
		while (++offset < FLASH_INDEX_USER_SIZE)
			g_flash_index.page[offset] = flash_get_byte_next();
		flash_get_byte_end();
		position = -1;
		while (++position < FLASH_INDEX_USER_PER_PAGE)
		{
			if (g_flash_index.index.user[position].inactive)
				return (position);
		}
	}
	return (-1);
}

s16		get_index_position_user(u8 *id, u8 checksum)
{
	u16	offset;
	u16	position;
	u16 pageslues;

	g_flash_index.index.page_number = FLASH_INDEX_PAGE_PER_CHECKSUM * checksum - 1;
	pageslues = -1;
	while (++pageslues < FLASH_INDEX_PAGE_MAX)
	{
		offset = 0;
		g_flash_index.index.page_number++;
		g_flash_index.page[0] = flash_get_byte_init(g_flash_index.index.page_number * FLASH_PAGE_SIZE);
		while (++offset < FLASH_INDEX_USER_SIZE)
			g_flash_index.page[offset] = flash_get_byte_next();
		flash_get_byte_end();
		position = -1;
		while (++position < FLASH_INDEX_USER_PER_PAGE)
		{
			if (is_id_equ(g_flash_index.index.user[position].id, id))
				return (position);
		}
	}
	return (-1);
}

void	db_adduser(u8 *id)
{
	u8	page = -1;
	u8	user;

	/*while (++page < 47)
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
	}*/
}

