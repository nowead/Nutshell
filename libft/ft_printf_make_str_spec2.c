/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_make_str_spec2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:30:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_make_str_malloc(t_format *spec)
{
	spec->obj_size = spec->str_len;
	if (spec->precision >= 0 && spec->obj_size < (size_t)spec->precision \
	&& 's' != spec->type)
		spec->obj_size = spec->precision;
	if (-1 == spec->sign || flag_is_on(spec->flags, FLAG_PLUS) \
	|| flag_is_on(spec->flags, FLAG_BLANK))
		(spec->obj_size)++;
	if ('p' == spec->type || (flag_is_on(spec->flags, FLAG_SHARP) \
	&& (NULL != spec->str)))
		spec->obj_size += 2;
	spec->trimmed_str_len = spec->obj_size;
	if (spec->obj_size < (size_t)spec->width)
		spec->obj_size = spec->width;
	return ((char *)malloc(sizeof(char) * spec->obj_size));
}

void	ft_printf_make_str_prefix(t_format *spec, char *str, size_t *i)
{
	if (-1 == spec->sign)
		str[(*i)++] = '-';
	else if (flag_is_on(spec->flags, FLAG_PLUS))
		str[(*i)++] = '+';
	else if (flag_is_on(spec->flags, FLAG_BLANK))
		str[(*i)++] = ' ';
	if ('p' == spec->type)
	{
		ft_memcpy(&str[*i], "0x", 2);
		(*i) += 2;
	}
	if (flag_is_on(spec->flags, FLAG_SHARP) && (NULL != spec->str))
	{
		if ('x' == spec->type)
			ft_memcpy(&str[*i], "0x", 2);
		else
			ft_memcpy(&str[*i], "0X", 2);
		(*i) += 2;
	}
}

void	ft_printf_make_str_precision(t_format *spec, char *str, size_t *i)
{
	int	padding;

	if ('s' != spec->type)
	{
		if (spec->precision > 0 && (size_t)spec->precision > spec->str_len)
		{
			padding = (size_t)spec->precision - spec->str_len;
			ft_memset(&str[*i], '0', padding);
			(*i) += padding;
		}
	}
}

void	ft_printf_make_str_width(t_format *spec, char *str, size_t *i)
{
	int	margin;

	if (spec->obj_size > spec->trimmed_str_len)
	{
		margin = spec->obj_size - spec->trimmed_str_len;
		if (flag_is_on(spec->flags, FLAG_ZERO))
			ft_memset(&str[*i], '0', margin);
		else
			ft_memset(&str[*i], ' ', margin);
		(*i) += margin;
	}
}

void	ft_printf_make_str_cpy_num(t_format *spec, char *str, size_t *i)
{
	ft_memcpy(&str[*i], spec->str, spec->str_len);
	(*i) += spec->str_len;
}
