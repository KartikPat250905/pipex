/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:32:19 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/29 13:32:25 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putcharint(char c, t_out *strutil)
{
	if (strutil->error == -1)
		return ;
	if (write(1, &c, 1) == -1)
		strutil->error = -1;
	strutil->total++;
}

void	ft_putint(int n, t_out *strutil)
{
	long	nb;

	if (strutil->error == -1)
		return ;
	nb = n;
	if (nb < 0)
	{
		if (write(1, "-", 1) == -1)
		{
			strutil->error = -1;
			return ;
		}
		nb *= -1;
		strutil->total++;
	}
	if (nb > 9)
	{
		ft_putint(nb / 10, strutil);
		ft_putcharint((nb % 10) + '0', strutil);
	}
	else
		ft_putcharint(nb + '0', strutil);
}

void	ft_printint(t_out *strutil, va_list ap)
{
	int	num;

	num = va_arg(ap, int);
	ft_putint(num, strutil);
	if (strutil->error != -1)
		strutil->strindex += 2;
}
