/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:13:00 by macbookair        #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	size_t	i;
	ssize_t	printbyte;
	size_t	total_printbyte;
	va_list	args;

	va_start(args, format);
	total_printbyte = 0;
	i = 0;
	while (format[i])
	{
		if ('%' == format[i])
			printbyte = ft_dprintf_print_format_string(fd, format, args, &i);
		else
			printbyte = ft_dprintf_print_plain_string(fd, format, &i);
		if (-1 == printbyte)
			break ;
		total_printbyte += printbyte;
	}
	va_end(args);
	if (-1 == printbyte)
		return (-1);
	return (total_printbyte);
}

int	ft_dprintf_print_format_string(int fd, const char *format, \
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
		printbyte = ft_dprintf_print_str(fd, &spec);
	if (-1 == error || -1 == printbyte)
		return (-1);
	return (printbyte);
}

int	ft_dprintf_print_plain_string(int fd, const char *format, size_t *i)
{
	const char	*start;
	size_t		len;
	ssize_t		printbyte;

	start = &format[*i];
	len = ft_printf_strlen(start);
	printbyte = write(fd, start, len);
	if (-1 == printbyte)
		return (-1);
	(*i) += printbyte;
	return (printbyte);
}

int	ft_dprintf_print_str(int fd, t_format *spec)
{
	ssize_t	printbyte;

	printbyte = write(fd, spec->str, spec->obj_size);
	free(spec->str);
	spec->str = NULL;
	return (printbyte);
}
