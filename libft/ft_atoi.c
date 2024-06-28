/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:51:34 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/22 15:20:39 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	resultcounter(int *result, int sign, char const *str, int i)
{
	while (ft_isdigit(str[i]))
	{
		if (*result > INT_MAX / 10 && sign == 1)
			return (-1);
		if (*result - (1 / 10) > (INT_MAX) / 10 && sign == -1)
			return (0);
		*result *= 10;
		*result += str[i] - '0';
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;
	int	checker;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	checker = resultcounter(&result, sign, str, i);
	if (checker == -1)
		return (-1);
	if (checker == 0)
		return (0);
	return (result * sign);
}
