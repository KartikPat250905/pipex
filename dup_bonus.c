/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:47:53 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/14 14:47:56 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	read_from_file(t_helper *helper, t_aae *aae)
{
	if (dup2(helper->fd[0][1], STDOUT_FILENO) == -1
			|| dup2(helper->inputfd, STDIN_FILENO) == -1)
	{
		if (helper -> inputfd != -1)
			perror("dup2");
		free_fdnspid(helper);
		exit (EXIT_FAILURE);
	}
	close (helper->inputfd);
	close_pipes(helper);
	execute(aae, aae->argv[2], helper);
}

void	out_to_file(t_helper *helper, t_aae *aae, int current)
{
	if (dup2(helper->outputfd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_fdnspid(helper);
		exit(EXIT_FAILURE);
	}
	if (close(helper->outputfd) == -1)
	{
		perror("close");
		free_fdnspid(helper);
		exit(EXIT_FAILURE);
	}
	if (dup2(helper->fd[current - 1][0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_fdnspid(helper);
		exit(EXIT_FAILURE);
	}
	close_pipes(helper);
	execute(aae, aae->argv[aae->ac - 2], helper);
}

void	read_from_pipe(t_helper *helper, t_aae *aae, int current)
{
	if (dup2(helper->fd[current - 1][0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_fdnspid(helper);
		exit(EXIT_FAILURE);
	}
	if (dup2(helper->fd[current][1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_fdnspid(helper);
		exit(EXIT_FAILURE);
	}
	close_pipes(helper);
	execute(aae, aae->argv[current + 2], helper);
}

void	free_fdnspid(t_helper *helper)
{
	if (helper -> pids != NULL)
		free(helper -> pids);
	if (helper->fd != NULL)
	{
		free(helper->fd);
		helper->fd = NULL;
	}
}
