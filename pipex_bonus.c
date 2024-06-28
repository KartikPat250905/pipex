/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:46:26 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/26 17:25:58 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_helper *helper, t_aae *aae, int current)
{
	if (current == 0)
		read_from_file(helper, aae);
	else if (current + 3 == aae->ac - 1)
		out_to_file(helper, aae, current);
	else
		read_from_pipe(helper, aae, current);
}

static int	pid_wait(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static int	wait_for_children(t_helper *helper)
{
	int	i;
	int	final_exit_status;

	i = 0;
	final_exit_status = 0;
	while (i < helper->cmdcnt)
	{
		final_exit_status = pid_wait(helper->pids[i]);
		final_exit_status = pid_wait(helper->pids[i]);
		i++;
	}
	return (final_exit_status);
}

void	pipex(t_helper *helper, t_aae *aae)
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = malloc(sizeof(pid_t) * helper->cmdcnt);
	helper -> pids = pid;
	while (i < helper->cmdcnt)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("Fork failed");
			free_fdnspid(helper);
			exit(1);
		}
		if (pid[i] == 0)
			child_process(helper, aae, i);
		i++;
	}
	close_pipes(helper);
	helper -> status = wait_for_children(helper);
	free_fdnspid(helper);
	exit(helper -> status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_aae		aae;
	t_helper	helper;

	if (argc < 5)
	{
		ft_putstr_fd("Incorrect usuage", 2);
		exit(1);
	}
	initstruct(argc, argv, envp, &aae);
	fdinit(&helper, argc);
	if (!fileopener(&helper, &aae))
		return (EXIT_FAILURE);
	create_pipes(helper);
	pipex(&helper, &aae);
}
