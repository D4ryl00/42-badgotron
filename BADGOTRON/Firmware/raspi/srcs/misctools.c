/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misctools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:00:58 by amordret          #+#    #+#             */
/*   Updated: 2018/08/09 16:47:54 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

char	*respond_getprefix(char *readbuffer)
{
	int		i;
	char	*prefix;

	i = 0;
	if ((prefix = malloc(30)) == NULL)
		error_and_exit("erreur malloc respondprefix");
	while (readbuffer[i])
	{
		if (readbuffer[i] == '_')
			break ;
		prefix[i] = readbuffer[i];
		i++;
	}
	prefix[i] = '\0';
	return (prefix);
}

char	*respond_getsuffix(char *readbuffer)
{
	int		i;
	int		j;
	char	*suffix;

	i = 0;
	j = 0;
	if ((suffix = malloc(41)) == NULL)
		error_and_exit("erreur malloc respondsuffix");
	while (readbuffer[i] && readbuffer[i] != '_')
		i++;
	i++;
	while (readbuffer[i] && j < 40)
	{
		suffix[j] = readbuffer[i];
		i++;
		j++;
	}
	suffix[j] = '\0';
	return (suffix);
}

void	respond_wtf(int fd)
{
	ft_putendl_fd("?", fd);
}