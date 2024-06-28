/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print%X.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:08:39 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/29 13:08:42 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printcx(unsigned int n, t_out *strutil);

void	ft_putchar_cx(char c, t_out *strutil)
{
	if (strutil->error == -1)
		return ;
	if (write(1, &c, 1) == -1)
	{
		strutil->error = -1;
		return ;
	}
	strutil->total++;
}

void	printcx(unsigned int n, t_out *strutil)
{
	unsigned int	nb;
	char			*base;

	base = "0123456789ABCDEF";
	if (strutil->error == -1)
		return ;
	nb = n;
	if (nb >= 16)
		printcx(nb / 16, strutil);
	ft_putchar_cx(*(base + (nb % 16)), strutil);
}

void	ft_printcx(t_out *strutil, va_list ap)
{
	unsigned int	num;

	num = va_arg(ap, unsigned int);
	printcx(num, strutil);
	if (strutil->error == -1)
		return ;
	strutil->strindex += 2;
}
