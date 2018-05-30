/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misctools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:00:58 by amordret          #+#    #+#             */
/*   Updated: 2018/05/30 16:08:37 by amordret         ###   ########.fr       */
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

void	respond_wtf(int fd)
{
	ft_putendl_fd("?", fd);
}