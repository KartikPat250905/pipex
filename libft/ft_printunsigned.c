/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:35:41 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/29 13:35:44 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putcharunsignedint(char c, t_out *strutil)
{
	if (strutil->error == -1)
		return ;
	if (write(1, &c, 1) == -1)
		strutil->error = -1;
	else
		strutil->total++;
}

void	ft_putunsigned(unsigned int n, t_out *strutil)
{
	unsigned int	nb;

	nb = n;
	if (nb > 9)
	{
		ft_putunsigned(nb / 10, strutil);
		ft_putcharunsignedint((nb % 10) + '0', strutil);
	}
	else
		ft_putcharunsignedint(nb + '0', strutil);
}

void	ft_printunsigned(t_out *strutil, va_list ap)
{
	unsigned int	num;

	num = va_arg(ap, unsigned int);
	ft_putunsigned(num, strutil);
	if (strutil->error != -1)
		strutil->strindex += 2;
}
