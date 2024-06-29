/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_read_spec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:20:41 by seonseo           #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_read_flags(const char *format, t_format *spec, size_t *i)
{
	while (1)
	{
		if ('-' == format[*i])
			spec->flags = spec->flags | FLAG_MINUS;
		else if ('+' == format[*i])
			spec->flags |= FLAG_PLUS;
		else if (' ' == format[*i])
			spec->flags |= FLAG_BLANK;
		else if ('#' == format[*i])
			spec->flags |= FLAG_SHARP;
		else if ('0' == format[*i])
			spec->flags |= FLAG_ZERO;
		else
			break ;
		(*i)++;
	}
}

int	ft_printf_read_width(const char *format, t_format *spec, size_t *i)
{
	while (ft_isdigit(format[*i]))
	{
		spec->width = spec->width * 10 + format[*i] - '0';
		if (spec->width >= INT_MAX)
			return (-1);
		(*i)++;
	}
	return (0);
}

int	ft_printf_read_precision(const char *format, t_format *spec, size_t *i)
{
	if ('.' == format[*i])
	{
		spec->precision = 0;
		(*i)++;
		while (ft_isdigit(format[*i]))
		{
			spec->precision = spec->precision * 10 + format[*i] - '0';
			if (spec->precision >= INT_MAX)
				return (-1);
			(*i)++;
		}
	}
	return (0);
}

int	ft_printf_read_type(const char *format, t_format *spec, size_t *i)
{
	int	j;

	j = 0;
	while ("cspdiuxX%"[j] && ("cspdiuxX%"[j] != format[*i]))
		j++;
	if ('\0' == "cspdiuxX%"[j])
		return (-1);
	spec->type = format[*i];
	(*i)++;
	return (0);
}
