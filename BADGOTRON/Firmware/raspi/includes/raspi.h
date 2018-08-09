/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raspi.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:30:12 by amordret          #+#    #+#             */
/*   Updated: 2018/08/09 16:27:33 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RASPI_H_

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
//# define AV0 "/home/pi/raspi/api.py"
# define AV0 "/home/adrien/ubuntu/elec/BADGOTRON/Firmware/raspi/api.py"

typedef struct tm	temps;

typedef struct	s_temps
{
	char		jour;
	char		joursem;
	char		mois;
	char		annee;
	char		heure;
	char		minute;
	char		seconde;
	char		isdst;
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
int					ft_strequ(char *s1, char *s2);
void				ft_strncpy(char *dest, char *src, size_t n);

char				*ft_strdup(char *str);
int					ft_strlen(char *str);
void				error_and_exit(char *str);
int					open_uart(void);
char				*read_uart(int fd);
void				get_temps(t_temps *now);
char				*respond_getprefix(char *readbuffer);
void				respond(char *readbuffer, int fd);
int					respond_time(char *readbuffer, int fd);
void				respond_wtf(int fd);
char				*whatsmyname(char *id);

#endif
