/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddress_buf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:15:46 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/29 13:15:50 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_ptr(char c, t_out *strutil)
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

void	ft_putstr_address(t_out *strutil, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_ptr(s[i], strutil);
		if (strutil->error == -1)
			return ;
		i++;
	}
}

void	ft_put_ptr(uintptr_t num, t_out *strutil)
{
	if (strutil->error == -1)
		return ;
	if (num >= 16)
	{
		ft_put_ptr(num / 16, strutil);
		ft_put_ptr(num % 16, strutil);
	}
	else
	{
		if (num <= 9)
			ft_putchar_ptr(num + '0', strutil);
		else
			ft_putchar_ptr(num - 10 + 'a', strutil);
	}
}

void	ft_putaddress(t_out *strutil, uintptr_t address)
{
	ft_putstr_address(strutil, "0x");
	ft_put_ptr(address, strutil);
}

void	ft_printaddress_buf(t_out *strutil, va_list ap)
{
	unsigned long long	ptr;
	unsigned long int	address;

	ptr = va_arg(ap, unsigned long long);
	if (ptr == 0)
	{
		ft_putstr_address(strutil, "0x0");
		if (strutil->error == -1)
			return ;
		strutil->strindex += 2;
		return ;
	}
	address = (unsigned long int)ptr;
	ft_putaddress(strutil, address);
	if (strutil->error == -1)
		return ;
	strutil->strindex += 2;
}
