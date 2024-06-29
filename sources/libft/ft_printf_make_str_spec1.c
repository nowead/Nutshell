/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_make_str_spec1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:00:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_make_str_spec(t_format *spec)
{
	char	*str;
	size_t	i;

	str = ft_printf_make_str_malloc(spec);
	if (NULL == str)
		return (-1);
	i = 0;
	if (!flag_is_on(spec->flags, FLAG_MINUS) && \
	!flag_is_on(spec->flags, FLAG_ZERO))
		ft_printf_make_str_width(spec, str, &i);
	ft_printf_make_str_prefix(spec, str, &i);
	ft_printf_make_str_precision(spec, str, &i);
	if (flag_is_on(spec->flags, FLAG_ZERO))
		ft_printf_make_str_width(spec, str, &i);
	ft_printf_make_str_cpy_num(spec, str, &i);
	if (flag_is_on(spec->flags, FLAG_MINUS))
		ft_printf_make_str_width(spec, str, &i);
	spec->str = str;
	return (0);
}
