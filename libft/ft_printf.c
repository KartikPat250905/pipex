/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:16 by karpatel          #+#    #+#             */
/*   Updated: 2024/05/08 11:57:54 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...);
int	num_args(const char *str);
int	isidentifier(const char *str, int i);

void	ft_printpercent(t_out *strutil)
{
	char	c;

	if (strutil->error == -1)
		return ;
	c = '%';
	if (write(1, &c, 1) == -1)
	{
		strutil->error = -1;
		return ;
	}
	strutil->strindex += 2;
	strutil->total++;
}

int	type(t_out *strutil)
{
	while (isidentifier(strutil->str, strutil->strindex))
	{
		if (strutil->str[strutil->strindex + 1] == 'c')
			return (0);
		else if (strutil->str[strutil->strindex + 1] == 's')
			return (1);
		else if (strutil->str[strutil->strindex + 1] == 'p')
			return (2);
		else if (strutil->str[strutil->strindex + 1] == 'd')
			return (3);
		else if (strutil->str[strutil->strindex + 1] == 'i')
			return (4);
		else if (strutil->str[strutil->strindex + 1] == 'u')
			return (5);
		else if (strutil->str[strutil->strindex + 1] == 'x')
			return (6);
		else if (strutil->str[strutil->strindex + 1] == 'X')
			return (7);
		else if (strutil->str[strutil->strindex + 1] == '%')
			return (8);
		strutil->strindex += 2;
	}
	return (-1);
}

void	checktype(t_out *strutil, va_list ap)
{
	int	x;

	x = type(strutil);
	if (x == 0)
		ft_putchar_buf(strutil, ap);
	else if (x == 1)
		ft_putstr_buf(strutil, ap);
	else if (x == 2)
		ft_printaddress_buf(strutil, ap);
	else if (x == 3)
		ft_printint(strutil, ap);
	else if (x == 4)
		ft_printint(strutil, ap);
	else if (x == 5)
		ft_printunsigned(strutil, ap);
	else if (x == 6)
		ft_printhex(strutil, ap);
	else if (x == 7)
		ft_printcx(strutil, ap);
	else if (x == 8)
		ft_printpercent(strutil);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_out	strutil;

	strutil.totalargs = num_args(str);
	strutil.str = str;
	strutil.strindex = 0;
	strutil.total = 0;
	strutil.error = 1;
	va_start(args, str);
	while (str[strutil.strindex] != '\0')
	{
		if (isidentifier(strutil.str, strutil.strindex))
		{
			if (strutil.error == -1)
				return (-1);
			checktype(&strutil, args);
		}
		else
		{
			if (write(1, &strutil.str[strutil.strindex++], 1) == -1)
				return (-1);
			strutil.total++;
		}
	}
	return (strutil.total);
}

int	isidentifier(const char *str, int i)
{
	if (str[i] == '%' && ((str[i + 1] == 'd' || str[i + 1] == 'c'
				|| str[i + 1] == 's' || str[i + 1] == 'p' || str[i + 1] == 'i'
				|| str[i + 1] == 'u' || str[i + 1] == 'x' || str[i + 1] == 'X'
				|| str[i + 1] == '%') || ((str[i + 1] == '+'
					|| str[i + 1] == ' '
					|| str[i + 1] == '#') && (str[i + 2] == 'd'
					|| str[i + 2] == 'c'
					|| str[i + 2] == 's' || str[i + 2] == 'p'
					|| str[i + 2] == 'i'
					|| str[i + 2] == 'u' || str[i + 2] == 'x'
					|| str[i + 2] == 'X'
					|| str[i + 2] == '%'))))
		return (1);
	return (0);
}
