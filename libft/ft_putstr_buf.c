/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:58:46 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/15 16:01:20 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_out *strutil)
{
	if (strutil->error == -1)
		return ;
	if (write(1, &c, 1) == -1)
		strutil->error = -1;
}

void	ft_putstr_buf(t_out *strutil, va_list ap)
{
	int		i;
	char	*s;

	i = 0;
	s = va_arg(ap, char *);
	if (!s)
	{
		strutil->total += 6;
		if (write(1, "(null)", 6) == -1)
		{
			strutil->error = -1;
			return ;
		}
		strutil->strindex += 2;
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], strutil);
		if (strutil->error == -1)
			return ;
		strutil->total++;
		i++;
	}
	strutil->strindex += 2;
}
