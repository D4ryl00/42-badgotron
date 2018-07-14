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
	u8 i;

	g_flash_index.index.page_number = FLASH_INDEX_PAGE_PER_CHECKSUM * checksum - 1;
	i = -1;
	while (++i < FLASH_INDEX_PAGE_PER_CHECKSUM)
	{
		offset = 0;
		g_flash_index.index.page_number++;
		g_flash_index.page[0] = flash_get_byte_init(g_flash_index.index.page_number * FLASH_PAGE_SIZE);
		while (++offset < FLASH_INDEX_USER_PAGE_SIZE)
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
	u8 i;

	g_flash_index.index.page_number = FLASH_INDEX_PAGE_PER_CHECKSUM * checksum - 1;
	i = -1;
	while (++i < FLASH_INDEX_PAGE_PER_CHECKSUM)
	{
		offset = 0;
		g_flash_index.index.page_number++;
		g_flash_index.page[0] = flash_get_byte_init(g_flash_index.index.page_number * FLASH_PAGE_SIZE);
		while (++offset < FLASH_INDEX_USER_PAGE_SIZE)
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

u8	db_get_user_data_page_position(u8 page_number, s16 index_position)
{
	u16	user_number;
	u16	users_prev_pages;

	users_prev_pages = page_number * FLASH_INDEX_USER_PER_PAGE;
	user_number = users_prev_pages + index_position;
	return (user_number / FLASH_DATA_USER_PER_PAGE + FLASH_INDEX_PAGE_NBR);
}

u32	db_get_user_data_page_address(u8 page_number, s16 index_position)
{
	return (db_get_user_data_page_position(page_number, index_position) * FLASH_PAGE_SIZE);
}

u8	db_get_user_data_position(u8 page_number, s16 index_position)
{
	u16	user_number;
	u16	users_prev_pages;

	users_prev_pages = page_number * FLASH_INDEX_USER_PER_PAGE;
	user_number = users_prev_pages + index_position;
	return (user_number % FLASH_DATA_USER_PER_PAGE);
}

void		db_get_data_page(u32 addr)
{
	u32 i;

	i = 0;
	g_flash_data.page[0] = flash_get_byte_init(addr);
	while (++i < FLASH_PAGE_SIZE)
		g_flash_data.page[i] = flash_get_byte_next();
	flash_get_byte_end();
	g_flash_data.data.page_number = addr / FLASH_PAGE_SIZE;
}

void		db_get_index_page(u32 addr)
{
	u32 i;

	i = 0;
	g_flash_index.page[0] = flash_get_byte_init(addr);
	while (++i < FLASH_PAGE_SIZE)
		g_flash_index.page[i] = flash_get_byte_next();
	flash_get_byte_end();
	g_flash_index.index.page_number = addr / FLASH_PAGE_SIZE;
}

void	init_user_data(t_data_user *data)
{
	u8	i;

	data->current_day = 0;
	data->current_month = 0;
	data->current_trimester = 0;
	data->current_week = 0;
	data->last_day = 0;
	data->last_month = 0;
	data->last_trimester = 0;
	data->last_week = 0;
	i = -1;
	while (++i < 7)
		data->sliding_days[i] = 0;
	data->timestamp = 0;
}

void	db_update_user_out_time(t_data_user *data)
{
	u16	minutes;

	minutes = (get_timestamp() - data->timestamp) / 60;
	data->timestamp = 0;
	data->current_day += minutes;
	data->current_month += minutes;
	data->current_week += minutes;
	data->current_trimester += minutes;
}

void	db_foreach(u8 (*f)(t_data_user *))
{
	u8	i;
	u16	j;
	u8	data_page;
	u32	data_page_address;
	u8	data_position;
	u8	is_modified;

	i = -1;
	is_modified = 0;
	while (++i < FLASH_INDEX_PAGE_NBR)
	{
		db_get_index_page(i * FLASH_PAGE_SIZE);
		j = -1;
		while (++j < FLASH_INDEX_USER_PER_PAGE)
		{
			if (!g_flash_index.index.user[j].inactive)
			{
				data_page = db_get_user_data_page_position(g_flash_index.index.page_number, j);
				data_page_address = db_get_user_data_page_address(g_flash_index.index.page_number, j);
				if (g_flash_data.data.page_number != data_page)
				{
					if (is_modified)
						flash_put_multibytes((g_flash_data.data.page_number	* FLASH_PAGE_SIZE)
								, g_flash_data.page, FLASH_PAGE_SIZE);
					db_get_data_page(data_page_address);
				}
				data_position = db_get_user_data_position(g_flash_index.index.page_number, j);
				is_modified |= f(&(g_flash_data.data.user[data_position]));
			}
		}
	}
	if (is_modified)
		flash_put_multibytes(data_page_address, g_flash_data.page, FLASH_PAGE_SIZE);
}