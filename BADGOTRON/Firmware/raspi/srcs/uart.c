/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:44:52 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 15:45:00 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

int		open_uart(void)
{
	int	fd;

	if ((fd = open("/dev/ttyAMA0", O_RDWR)) == -1)
		error_and_exit("could not open /dev/ttyAMA0");
	return (fd);
}

char	*read_uart(int fd)
{
	char 	str[250];
	char	*out;
	int		i;
	char	c;

	i = 0;
	c = 'a';
	while (c != '\n')
	{
		read(fd, &c, 1);
		str[i] = c;
		if (c != '\n')
			i++;
	}
	str[i] = '\0';
	if ((out = malloc(i + 1)) == NULL)
		error_and_exit("error mallocing buffer");
	i = 0;
	while (str[i])
	{
		out[i] = str[i];
		i++;
		if (i > 230)
			error_and_exit("read buffer overflow");
	}
	return (out);
}
