/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_make_str_cs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:23:44 by seonseo           #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_make_str_c(t_format *spec, char c)
{
	char	str_c[1];

	str_c[0] = c;
	spec->str = str_c;
	spec->str_len = 1;
	return (ft_printf_make_str_spec(spec));
}

int	ft_printf_make_str_s(t_format *spec, char *s)
{
	if (NULL == s)
	{
		spec->str = "(null)";
		spec->str_len = 6;
	}
	else
	{
		spec->str = s;
		spec->str_len = ft_strlen(s);
	}
	if (-1 != spec->precision && spec->str_len > (size_t)spec->precision)
		spec->str_len = (size_t)spec->precision;
	return (ft_printf_make_str_spec(spec));
}
