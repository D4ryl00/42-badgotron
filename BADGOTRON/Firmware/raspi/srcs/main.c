/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:29:48 by amordret          #+#    #+#             */
/*   Updated: 2018/08/09 16:29:53 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

int		main(void)
{
	//char	*readbuffer;
	//int		fd;
	char	*test;
	char	*test2;

	/*fd = open_uart();
	while (42)
	{
		readbuffer = read_uart(fd);
		ft_putendl(readbuffer);
		respond(readbuffer, fd);
		ft_putstr_fd("\n", fd);
	}*/
	test = ft_strdup("23");
	test2 = whatsmyname(test);
	ft_putendl(test2);
	free(test2);
	//close(fd);
	return (0);
}
