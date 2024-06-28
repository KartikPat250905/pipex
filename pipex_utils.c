/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_t_utils.c                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:44:25 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/13 15:44:27 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//free paths in pathfinder
char	*pathcheck(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	if (!cmd || *cmd == '\0')
		return (NULL);
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*pathfinder(char *envp[], char *cmd)
{
	char	**paths;
	char	*str;
	char	*result;
	int		i;

	i = 0;
	str = NULL;
	if (!cmd || *cmd == '\0')
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			str = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (str == NULL)
		return (NULL);
	paths = ft_split(str, ':');
	result = pathcheck(paths, cmd);
	free(paths);
	return (result);
}

void	execute(char *cmd, char *envp[])
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
		exit(EXIT_FAILURE);
	if (!*cmds)
	{
		ft_putstr_fd("pipex: Empty commands\n", 2);
		exit(126);
	}
	path = exechelper(cmds, envp);
	if (execve(path, cmds, envp) == -1)
	{
		perror("execve");
		exit(126);
	}
}

void	childprocess1(char *argv[], char *envp[], t_util *helper)
{
	if (dup2(helper->fd[1], STDOUT_FILENO) == -1
		|| dup2(helper->inputfd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(helper->fd[0]);
	close(helper->fd[1]);
	close(helper->inputfd);
	close(helper->outputfd);
	execute(argv[2], envp);
}

void	childprocess2(char *argv[], char *envp[], t_util *helper)
{
	if (dup2(helper->fd[0], STDIN_FILENO) == -1
		|| dup2(helper->outputfd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(helper->fd[0]);
	close(helper->fd[1]);
	close(helper->outputfd);
	close(helper->inputfd);
	execute(argv[3], envp);
}
