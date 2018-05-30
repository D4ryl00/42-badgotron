/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:29:48 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 15:37:01 by amordret         ###   ########.fr       */
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

int		main(void)
{
	//char	*readbuffer;
	int		fd;
	t_temps	now;

	fd = open_uart();
	//readbuffer = read_uart(fd);
	//ft_putendl(readbuffer);
	get_temps(&now);
	ft_putnbr_fd(now.jour, fd);
	ft_putchar_fd('/', fd);
	ft_putnbr_fd(now.mois, fd);
	ft_putchar_fd('/', fd);
	ft_putnbr_fd(now.annee, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(now.heure, fd);
	ft_putchar_fd(':', fd);
	ft_putnbr_fd(now.minute, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	return (0);
}
