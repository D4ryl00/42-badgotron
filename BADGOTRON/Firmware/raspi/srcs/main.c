/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:29:48 by amordret          #+#    #+#             */
/*   Updated: 2018/08/09 17:06:33 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

int		main(void)
{
	char	*readbuffer;
	int		fd;

	/*		DEBUT PROD !!!!
	
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
			FIN PROD
	*/
	
	
	// debug a partir dici
	fd = 1;
	readbuffer = ft_strdup("name_32409234");
	respond(readbuffer, fd);
	free(readbuffer);
	readbuffer = ft_strdup("time_wday?");
	respond(readbuffer, fd);

	// A REMETTRE EN PROD
	return (0);
}
