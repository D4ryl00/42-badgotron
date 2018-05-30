/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raspi.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:30:12 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 15:27:14 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RASPI_H_

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>

typedef struct tm	temps;

typedef struct	s_temps
{
	char		jour;
	char		mois;
	char		annee;
	char		heure;
	char		minute;
	char		seconde;
	time_t		epoch;
}				t_temps;

void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putendl(char *str);
void				ft_putnbr(int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
void				ft_putendl_fd(char *str, int fd);
void				ft_putnbr_fd(int c, int fd);
void				error_and_exit(char *str);
char				*read_uart(int fd);
void				get_temps(t_temps *now);






#endif