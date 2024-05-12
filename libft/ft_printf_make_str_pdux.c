/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_make_str_pdux.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:30:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_make_str_p(t_format *spec, void *p)
{
	unsigned long long	p_llu;
	char				str_p[16];
	int					i;

	p_llu = (unsigned long long)p;
	i = 15;
	while (1)
	{
		str_p[i] = "0123456789abcdef"[p_llu % 16];
		p_llu /= 16;
		(spec->str_len)++;
		if (0 == p_llu)
			break ;
		i--;
	}
	spec->str = &str_p[i];
	return (ft_printf_make_str_spec(spec));
}

int	ft_printf_make_str_d(t_format *spec, int d)
{
	char	str_d[10];
	int		i;

	if (d < 0)
		spec->sign = -1;
	i = 9;
	while (0 != d)
	{
		if (-1 == spec->sign)
			str_d[i] = "0123456789"[-(d % 10)];
		else
			str_d[i] = "0123456789"[d % 10];
		d /= 10;
		(spec->str_len)++;
		if (0 == d)
			break ;
		i--;
	}
	if (0 == spec->str_len && -1 == spec->precision)
		spec->precision = 1;
	if (0 != spec->str_len)
		spec->str = &str_d[i];
	return (ft_printf_make_str_spec(spec));
}

int	ft_printf_make_str_u(t_format *spec, unsigned int u)
{
	char	str_u[10];
	int		i;

	i = 9;
	while (0 != u)
	{
		str_u[i] = "0123456789"[u % 10];
		u /= 10;
		(spec->str_len)++;
		if (0 == u)
			break ;
		i--;
	}
	if (0 == spec->str_len && -1 == spec->precision)
		spec->precision = 1;
	if (0 != spec->str_len)
		spec->str = &str_u[i];
	return (ft_printf_make_str_spec(spec));
}

int	ft_printf_make_str_x(t_format *spec, unsigned int u, char *base)
{
	char	str_x[8];
	int		i;

	i = 7;
	while (0 != u)
	{
		str_x[i] = base[u % 16];
		u /= 16;
		(spec->str_len)++;
		if (0 == u)
			break ;
		i--;
	}
	if (0 == spec->str_len && -1 == spec->precision)
		spec->precision = 1;
	if (0 != spec->str_len)
		spec->str = &str_x[i];
	return (ft_printf_make_str_spec(spec));
}
