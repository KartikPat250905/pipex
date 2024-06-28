/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:55:02 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/14 14:55:04 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

typedef struct s_aae
{
	int		ac;
	char	**argv;
	char	**envp;
}			t_aae;

typedef struct s_helper
{
	int		(*fd)[2];
	int		cmdcnt;
	int		inputfd;
	int		outputfd;
	int		status;
	pid_t	*pids;
}				t_helper;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
void	fdinit(t_helper *helper, int argc);
void	free_fdnspid(t_helper *helper);
void	initstruct(int argc, char *argv[], char *envp[], t_aae *aae);
void	create_pipes(t_helper helper);
void	close_pipes(t_helper *helper);
int		fileopener(t_helper *helper, t_aae *aae);
char	*pathcheck(char **paths, char *cmd);
char	*pathfinder(char *envp[], char *cmd);
void	execute(t_aae *aae, char *cmd, t_helper *helper);
void	read_from_file(t_helper *helper, t_aae *aae);
void	out_to_file(t_helper *helper, t_aae *aae, int current);
void	read_from_pipe(t_helper *helper, t_aae *aae, int current);

#endif
