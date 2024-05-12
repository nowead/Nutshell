/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_format_string.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:18:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_read_spec(const char *format, t_format *spec, size_t *i)
{
	int	error;

	ft_printf_read_flags(format, spec, i);
	error = ft_printf_read_width(format, spec, i);
	if (-1 != error)
		error = ft_printf_read_precision(format, spec, i);
	if (-1 != error)
		error = ft_printf_read_type(format, spec, i);
	return (error);
}

int	flag_is_on(int flags, int flag)
{
	if (flag == (flags & flag))
		return (1);
	return (0);
}

int	ft_printf_check_spec(t_format *spec)
{
	if ('d' != spec->type && 'i' != spec->type)
	{
		if (flag_is_on(spec->flags, FLAG_PLUS))
			spec->flags = (spec->flags ^ FLAG_PLUS);
		if (flag_is_on(spec->flags, FLAG_BLANK))
			spec->flags = (spec->flags ^ FLAG_BLANK);
	}
	if (flag_is_on(spec->flags, FLAG_SHARP))
		if ('x' != spec->type && 'X' != spec->type)
			return (-1);
	if (-1 != spec->precision)
		if ('c' == spec->type || 'p' == spec->type)
			spec->precision = -1;
	if (flag_is_on(spec->flags, FLAG_ZERO))
	{
		if ('c' == spec->type || 's' == spec->type)
			spec->flags = (spec->flags ^ FLAG_ZERO);
		if (flag_is_on(spec->flags, FLAG_MINUS) || -1 != spec->precision)
			spec->flags = (spec->flags ^ FLAG_ZERO);
	}
	return (0);
}

int	ft_printf_make_str(t_format *spec, va_list args)
{
	int		error;
	char	type;

	error = -1;
	type = spec->type;
	if ('c' == type)
		error = ft_printf_make_str_c(spec, va_arg(args, int));
	else if ('s' == type)
		error = ft_printf_make_str_s(spec, va_arg(args, char *));
	else if ('p' == type)
		error = ft_printf_make_str_p(spec, va_arg(args, void *));
	else if ('d' == type || 'i' == type)
		error = ft_printf_make_str_d(spec, va_arg(args, int));
	else if ('u' == type)
		error = ft_printf_make_str_u(spec, va_arg(args, unsigned int));
	else if ('x' == type)
		error = ft_printf_make_str_x(spec, va_arg(args, unsigned int), \
		"0123456789abcdef");
	else if ('X' == type)
		error = ft_printf_make_str_x(spec, va_arg(args, unsigned int), \
		"0123456789ABCDEF");
	else if ('%' == type)
		error = ft_printf_make_str_c(spec, '%');
	return (error);
}

int	ft_printf_print_str(t_format *spec, size_t *printbyte)
{
	int	error;

	error = write(1, spec->str, spec->obj_size);
	free(spec->str);
	spec->str = NULL;
	(*printbyte) += spec->obj_size;
	if (-1 == error)
		return (-1);
	return (0);
}
