/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:36:44 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/26 17:19:46 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fdinit(t_helper *helper, int argc)
{
	helper->cmdcnt = argc - 3;
	helper->pids = NULL;
	helper->fd = malloc (sizeof (int [2]) * (helper->cmdcnt - 1));
}

void	initstruct(int argc, char *argv[], char *envp[], t_aae *aae)
{
	aae->ac = argc;
	aae->argv = argv;
	aae->envp = envp;
}

void	create_pipes(t_helper helper)
{
	int	i;

	i = 0;
	while (i < helper.cmdcnt - 1)
	{
		if (pipe(helper.fd[i]) == -1)
		{
			perror("pipe");
			free_fdnspid(&helper);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(t_helper *helper)
{
	int	i;

	i = 0;
	while (i < helper->cmdcnt - 1)
	{
		if (close(helper->fd[i][0]) == -1)
			perror("close");
		if (close(helper->fd[i][1]) == -1)
			perror("close");
		i++;
	}
	close(helper->inputfd);
	close(helper->outputfd);
}

int	fileopener(t_helper *helper, t_aae *aae)
{
	int	o;

	helper->inputfd = open(aae->argv[1], O_RDONLY);
	if (helper -> inputfd == -1)
		perror(aae -> argv[1]);
	o = open(aae->argv[aae->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	helper->outputfd = o;
	if (helper->outputfd == -1)
	{
		free_fdnspid(helper);
		perror("Error opening output file");
		close(helper->inputfd);
		return (0);
	}
	return (1);
}
