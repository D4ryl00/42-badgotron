/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:29:48 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 16:19:53 by amordret         ###   ########.fr       */
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
		ft_putendl(readbuffer);
		respond(readbuffer, fd);
		ft_putstr_fd("\n", fd);
	}
	close(fd);
	return (0);
}
