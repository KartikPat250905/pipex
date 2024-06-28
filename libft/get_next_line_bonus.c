/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:12:06 by karpatel          #+#    #+#             */
/*   Updated: 2024/06/20 11:11:02 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin_gnl_bonus(buffer, buf);
	free(buffer);
	return (temp);
}

char	*get_line_inbuf(int fd, char *buffer)
{
	char	*buf;
	int		bytes_read;

	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	bytes_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buf)
	{
		free(buffer);
		return (NULL);
	}
	buffer = helper(fd, bytes_read, buf, buffer);
	if (buffer == NULL)
		return (NULL);
	free (buf);
	return (buffer);
}

char	*extractline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*cleanbuf(char *buffer)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new = ft_calloc(ft_strlen(buffer) - i + 1, 1);
	if (!new)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i] != '\0')
		new[j++] = buffer[i++];
	free(buffer);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = get_line_inbuf(fd, buffer[fd]);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = extractline(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = cleanbuf(buffer[fd]);
	return (line);
}
