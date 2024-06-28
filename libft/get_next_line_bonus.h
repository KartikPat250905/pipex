/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:12:24 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/20 11:11:17 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);
char	*ft_strchr(const char *string, int searchedChar);
void	*ft_calloc(size_t elementCount, size_t elementSize);
char	*ft_strjoin_gnl_bonus(char const *s1, char const *s2);
size_t	ft_strlen(const char *theString);
char	*ft_free(char *buffer, char *buf);
char	*helper(int fd, int bytes_read, char *buf, char *buffer);

#endif
