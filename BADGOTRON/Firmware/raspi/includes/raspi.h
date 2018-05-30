/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raspi.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:30:12 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 11:49:24 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RASPI_H_

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putendl(char *str);
void	error_and_exit(char *str);
char	*read_uart(int fd);



#endif