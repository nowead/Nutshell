/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:13:00 by macbookair        #+#    #+#             */
/*   Updated: 2024/04/22 13:57:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	size_t	i;
	ssize_t	printbyte;
	size_t	total_printbyte;
	va_list	args;
	t_str	dst;

	if (0 != size)
		*str = '\0';
	dst.str = str;
	dst.size = size;
	total_printbyte = 0;
	va_start(args, format);
	i = 0;
	while (format[i] && -1 != printbyte)
	{
		if ('%' == format[i])
			printbyte = ft_snprintf_print_format_string(&dst, format, args, &i);
		else
			printbyte = ft_snprintf_print_plain_string(&dst, format, &i);
		total_printbyte += printbyte;
	}
	va_end(args);
	if (-1 == printbyte)
		return (-1);
	return (total_printbyte);
}

int	ft_snprintf_print_format_string(t_str *dst, const char *format, \
va_list args, size_t *i)
{
	t_format	spec;
	int			error;
	ssize_t		printbyte;

	(*i)++;
	spec = (t_format){};
	spec.precision = -1;
	error = 0;
	error = ft_printf_read_spec(format, &spec, i);
	if (-1 != error)
		error = ft_printf_check_spec(&spec);
	if (-1 != error)
		error = ft_printf_make_str(&spec, args);
	if (-1 != error)
		printbyte = ft_snprintf_print_str(dst, &spec);
	if (-1 == error || -1 == printbyte)
		return (-1);
	return (printbyte);
}

int	ft_snprintf_print_plain_string(t_str *dst, const char *format, size_t *i)
{
	const char	*start;
	size_t		len;
	ssize_t		printbyte;

	start = &format[*i];
	len = ft_printf_strlen(start);
	printbyte = ft_strlncat(dst->str, start, dst->size, len);
	if (-1 == printbyte)
		return (-1);
	(*i) += printbyte;
	return (printbyte);
}

int	ft_snprintf_print_str(t_str *dst, t_format *spec)
{
	ssize_t	printbyte;

	printbyte = ft_strlncat(dst->str, spec->str, dst->size, spec->obj_size);
	free(spec->str);
	spec->str = NULL;
	return (printbyte);
}
