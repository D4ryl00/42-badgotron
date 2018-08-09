/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amordret <amordret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:58:44 by amordret          #+#    #+#             */
/*   Updated: 2018/08/09 14:58:44 by amordret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raspi.h"

int		checkid(char *id)
{
	int i;

	i = 0;
	while (id[i])
	{
		if (!(id[i] > 47 && id[i] < 58))
			return (1);
			i++;
	}
	return (0);
}

char	*whatsmyname(char *id)
{
	char	*name;
	int		pipeu[2];
	char	**av;
	pid_t	pid;
	char	c;
	int		i;

	i = 0;
	name = malloc(21);
	av = malloc(sizeof(*av) * 2);
	av[0] = ft_strdup(AV0);
	av[1] = ft_strdup(id);
	if (pipe(pipeu) == -1)
	{
		strcpy(name, "PIPE ERROR");
		return (name);
	}
	if ((pid = fork()) == -1)
	{
		strcpy(name, "FORK ERROR");
		return (name);
	}
	if (pid == 0)
	{
		//fils
		dup2 (pipeu[1], STDOUT_FILENO);
    	close(pipeu[0]);
    	//close(pipeu[1]);
		execve(AV0, av, NULL);
	}
	else
	{
		//pere
		close(pipeu[1]);
		c = 'a';
		while (i < 20 && c != '\0' && c != '\n')
		{
			read(pipeu[0], &c, 1);
			name[i] = c;
			i++;
			if (c == '\0' || c == '\n')
				break ;
			//wait(NULL);
		}
		name[i] = '\0';
		free(av[0]);
		free(av[1]);
		free(av);
	}
	
	return (name);
}