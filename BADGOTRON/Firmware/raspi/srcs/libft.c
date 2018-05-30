/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:41:14 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 15:26:44 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int c)
{
	if (c < 0)
		c = -c;
	if (c < 10)
		return (ft_putchar(c + 48));
	else
	{
		ft_putnbr(c / 10);
		ft_putchar(c%10 + 48);
	}
}

void	ft_putnbr_fd(int c, int fd)
{
	if (c < 0)
		c = -c;
	if (c < 10)
		return (ft_putchar_fd(c + 48, fd));
	else
	{
		ft_putnbr_fd(c / 10, fd);
		ft_putchar_fd(c%10 + 48, fd);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putendl(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}
