/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:46:26 by karpatel          #+#    #+#             */
/*   Updated: 2024/05/17 12:06:18 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// Handle leaks somehow

char	*exechelper(char **cmds, char *envp[])
{
	char	*path;

	if (access(cmds[0], F_OK) == 0)
	{
		if (access(cmds[0], X_OK) == 0)
			path = cmds[0];
		else
		{
			perror("pipex");
			exit(126);
		}
	}
	else
	{
		path = pathfinder(envp, cmds[0]);
		if (path == NULL)
		{
			perror("pipex");
			exit(127);
		}
	}
	return (path);
}

void	childcaller(char *argv[], char *envp[], t_util *helper)
{
	if (helper->pid1 == 0)
	{
		childprocess1(argv, envp, helper);
	}
	if (helper->pid2 == 0)
	{
		childprocess2(argv, envp, helper);
	}
	close(helper->fd[0]);
	close(helper->fd[1]);
}

int	fileopener(t_util *helper, char *argv[])
{
	helper->inputfd = open(argv[1], O_RDONLY);
	if (helper->inputfd == -1)
	{
		perror(argv[1]);
	}
	helper->outputfd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (helper->outputfd == -1)
	{
		perror(argv[4]);
		close(helper->inputfd);
		return (0);
	}
	if (pipe(helper->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	helperfun(t_util *helper, char *argv[], char *envp[])
{
	helper->pid1 = fork();
	if (helper->pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (helper->pid1 != 0)
		helper->pid2 = fork();
	if (helper->pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	childcaller(argv, envp, helper);
	if (helper->pid1 != 0 && helper->pid2 != 0)
	{
		close(helper->fd[0]);
		close(helper->fd[1]);
		close(helper->inputfd);
		close(helper->outputfd);
		waitpid(helper->pid1, &helper->status, 0);
		waitpid(helper->pid2, &helper->status, 0);
		if (WIFEXITED(helper->status))
			exit(WEXITSTATUS(helper->status));
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_util	helper;

	helper.pid1 = 0;
	helper.pid2 = 0;
	if (argc == 5)
	{
		if (!fileopener(&helper, argv))
			return (EXIT_FAILURE);
		helperfun(&helper, argv, envp);
	}
	else
	{
		ft_putstr_fd("Usuage: file1 cmd1 cmd2 file2", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
