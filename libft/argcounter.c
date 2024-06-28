/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcounter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:01:36 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/29 14:01:41 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	num_args(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (isidentifier(str, i))
			count++;
		i++;
	}
	return (count);
}
