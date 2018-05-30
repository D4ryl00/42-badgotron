/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:29:48 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 16:40:25 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

int		main(void)
{
	char	*readbuffer;
	int		fd;

	fd = open_uart();
	while (42)
	{
		readbuffer = read_uart(fd);
		respond(readbuffer, fd);
	}
	close(fd);
	return (0);
}
