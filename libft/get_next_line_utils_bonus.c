/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:12:38 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/20 11:11:02 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*helper(int fd, int bytes_read, char *buf, char *buffer)
{
	while (bytes_read > 0 && ! ft_strchr(buf, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		(buf[bytes_read]) = '\0';
		buffer = ft_free(buffer, buf);
		if (!buffer)
		{
			free(buf);
			return (NULL);
		}
	}
	return (buffer);
}

char	*ft_strchr(const char *string, int searchedChar)
{
	char	*str;
	int		i;

	str = (char *)string;
	i = 0;
	while (str[i] != (char)searchedChar && str[i] != '\0')
		i++;
	if (str[i] == searchedChar)
		return (str + i);
	else
		return (NULL);
}

char	*ft_strjoin_gnl_bonus(char const *s1, char const *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[sizetotal] = 0;
	return (res);
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*res;
	size_t	i;

	res = malloc(elementSize * elementCount);
	if (!res)
		return (NULL);
	i = 0;
	while (i < elementCount)
	{
		res[i] = '\0';
		i++;
	}
	return (res);
}

size_t	ft_strlen(const char *theString)
{
	int	i;

	i = 0;
	if (theString == NULL)
		return (0);
	while (theString[i])
		i++;
	return (i);
}
