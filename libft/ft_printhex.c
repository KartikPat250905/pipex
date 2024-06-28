/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:21:59 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/29 13:22:02 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hexcalc(unsigned int n, t_out *strutil);

void	ft_putchar_hex(char c, t_out *strutil)
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

void	print_hexcalc(unsigned int n, t_out *strutil)
{
	unsigned int	nb;
	char			*base;

	base = "0123456789abcdef";
	if (strutil->error == -1)
		return ;
	nb = n;
	if (nb >= 16)
		print_hexcalc(nb / 16, strutil);
	ft_putchar_hex(*(base + (nb % 16)), strutil);
}

void	ft_printhex(t_out *strutil, va_list ap)
{
	unsigned int	num;

	num = va_arg(ap, unsigned int);
	print_hexcalc(num, strutil);
	if (strutil->error == -1)
		return ;
	strutil->strindex += 2;
}
