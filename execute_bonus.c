/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:41:21 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/14 14:41:22 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	int		i;
	char	*result;

	str = NULL;
	i = 0;
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

char	*exechelper(char **cmds, char *envp[], t_helper *helper)
{
	char	*path;

	if (access(cmds[0], F_OK) == 0)
	{
		if (access(cmds[0], X_OK) == 0)
			path = cmds[0];
		else
		{
			free_fdnspid(helper);
			perror("pipex");
			exit(126);
		}
	}
	else
	{
		path = pathfinder(envp, cmds[0]);
		if (path == NULL)
		{
			free_fdnspid(helper);
			perror("pipex");
			exit(127);
		}
	}
	return (path);
}

void	execute(t_aae *aae, char *cmd, t_helper *helper)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
	{
		free_fdnspid(helper);
		exit(EXIT_FAILURE);
	}
	if (!*cmds)
	{
		ft_putstr_fd("pipex: Empty commands\n", 2);
		exit(126);
	}
	path = exechelper(cmds, aae->envp, helper);
	if (execve(path, cmds, aae->envp) == -1)
	{
		perror("execve");
		free_fdnspid(helper);
		exit(126);
	}
}
