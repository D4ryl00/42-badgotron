/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   respond.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:38:56 by amordret          #+#    #+#             */
/*   Updated: 2018/08/09 17:04:52 by amordret         ###   ########.fr       */
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
	else if (ft_strequ(prefix, "name"))
	{
		if (respond_name(readbuffer, fd))
			return ;
		else
			return (respond_wtf(fd));
	}
	else
		return (respond_wtf(fd));
}

int		respond_name(char *readbuffer, int fd)
{
	char	*name;

	if (checkid(respond_getsuffix(readbuffer)))
		return (0);
	name = whatsmyname(respond_getsuffix(readbuffer));
	ft_putendl_fd(name, fd);
	free(name);
	return (1);
}

int		respond_time(char *readbuffer, int fd)
{
	t_temps	now;

	get_temps(&now);
	if (ft_strequ(readbuffer, "time_wday?"))
	{
		ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.joursem, fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_day?"))
	{
		if (now.jour < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.jour, fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_month?"))
	{
		if (now.mois < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.mois, fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_year?"))
	{
		ft_putnbr_fd(now.annee, fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_hour?"))
	{
		if (now.heure < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.heure, fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_minute?"))
	{
		if (now.minute < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.minute, fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_second?"))
	{
		if (now.seconde < 10)
			ft_putchar_fd('0', fd);
		ft_putnbr_fd(now.seconde, fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	if (ft_strequ(readbuffer, "time_dst?"))
	{
		ft_putchar_fd('0', fd);			
		if (now.isdst == 1)
			ft_putchar_fd('1', fd);
		else
			ft_putchar_fd('0', fd);
		ft_putchar_fd('\n', fd);
		return (1) ;
	}
	return  (0);
}

