/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:48:15 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/13 15:48:16 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

typedef struct s_helper
{
	int	pid1;
	int	pid2;
	int	fd[2];
	int	inputfd;
	int	status;
	int	outputfd;
}				t_util;

char	**ft_split(char const *s, char c);
void	childprocess2(char *argv[], char *envp[], t_util *helper);
void	childprocess1(char *argv[], char *envp[], t_util *helper);
size_t	ft_strlen(const char *str);
char	*exechelper(char **cmds, char *envp[]);
char	*pathfinder(char *envp[], char *cmd);

#endif
