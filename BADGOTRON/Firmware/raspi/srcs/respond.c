/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   respond.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:38:56 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 16:35:28 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

void	respond(char *readbuffer, int fd)
{
	char	*prefix;

	prefix = respond_getprefix(readbuffer);
	if (ft_strequ(prefix, "time"))
		if (respond_time(readbuffer, fd))
			return ;
		else
			return (respond_wtf(fd));
	else
		return (respond_wtf(fd));
}

int		respond_time(char *readbuffer, int fd)
{
	t_temps	now;

	get_temps(&now);
	if (ft_strequ(readbuffer, "time_day?"))
	{
		if (now.jour < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.jour, fd);
		ft_putchar('\n');
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_month?"))
	{
		if (now.mois < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.mois, fd);
		ft_putchar('\n');
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_year?"))
	{
		ft_putnbr_fd(now.annee, fd);
		ft_putchar('\n');
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_hour?"))
	{
		if (now.heure < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.heure, fd);
		ft_putchar('\n');
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_minute?"))
	{
		if (now.minute < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.minute, fd);
		ft_putchar('\n');
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_second?"))
	{
		if (now.seconde < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.seconde, fd);
		ft_putchar('\n');
		return (1) ;
	}
	return  (0);
}

