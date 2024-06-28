/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:24:07 by karpatel          #+#    #+#             */
/*   Updated: 2024/04/29 13:27:19 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_main
{
	int			total;
	const char	*str;
	int			strindex;
	int			totalargs;
	int			error;
}				t_out;

int		ft_printf(const char *str, ...);
int		num_args(const char *str);
int		isidentifier(const char *str, int i);
void	ft_putchar_buf(t_out *strutil, va_list ap);
void	ft_printaddress_buf(t_out *strutil, va_list ap);
void	ft_putchar(char c, t_out *strutil);
void	ft_printhex(t_out *strutil, va_list ap);
void	ft_putstr_buf(t_out *strutil, va_list ap);
void	print_hexcalc(unsigned int n, t_out *strutil);
void	ft_printint(t_out *strutil, va_list ap);
void	ft_printunsigned(t_out *strutil, va_list ap);
void	ft_printcx(t_out *strutil, va_list ap);
int		num_args(const char *str);
void	ft_putint(int n, t_out *strutil);
void	checktype(t_out *strutil, va_list ap);
void	printcx(unsigned int n, t_out *strutil);

#endif
