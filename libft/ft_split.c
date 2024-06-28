/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:39:55 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/22 15:06:47 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c);
static size_t	strlen_mod(char const *s, char c);
static void		*free_memory(char **res, char **res_start);

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	**res_start;

	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res_start = res;
	while (*s)
	{
		if (*s != c)
		{
			*(res++) = malloc(sizeof(char) * (strlen_mod(s, c) + 1));
			if (!*(res - 1))
			{
				free_memory(res, res_start);
				return (NULL);
			}
			ft_strlcpy(*(res - 1), s, strlen_mod(s, c) + 1);
			s += strlen_mod(s, c);
		}
		if (*s != '\0')
			s++;
	}
	*res = NULL;
	return (res_start);
}

static size_t	strlen_mod(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (i == 0 && s[i] != c)
			count++;
		if (i > 0 && s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static void	*free_memory(char **res, char **res_start)
{
	while (res > res_start)
		free(*(--res));
	free(res_start);
	return (NULL);
}
