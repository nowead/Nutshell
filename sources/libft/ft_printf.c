/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:13:00 by macbookair        #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	size_t	i;
	size_t	printbyte;
	int		error;
	va_list	args;

	va_start(args, format);
	error = 0;
	printbyte = 0;
	i = 0;
	while (format[i] && -1 != error)
	{
		if ('%' == format[i])
			error = ft_printf_print_format_string(format, args, &i, &printbyte);
		else
			error = ft_printf_print_plain_string(format, &i, &printbyte);
	}
	va_end(args);
	if (-1 == error)
		return (-1);
	return (printbyte);
}

int	ft_printf_print_format_string(const char *format, va_list args, \
size_t *i, size_t *printbyte)
{
	t_format	spec;
	int			error;

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
		error = ft_printf_print_str(&spec, printbyte);
	return (error);
}

int	ft_printf_print_plain_string(const char *format, \
size_t *i, size_t *printbyte)
{
	const char	*start;
	size_t		len;

	start = &format[*i];
	len = ft_printf_strlen(start);
	if (write(1, start, len) == -1)
		return (-1);
	(*i) += len;
	(*printbyte) += len;
	return (0);
}

size_t	ft_printf_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != '%')
		len++;
	return (len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	a;
// 	int	printbyte;

// 	a = 'a';
// 	printbyte = ft_printf("%X%%\n", a);
// 	printf("\npb:%d\n", printbyte);
// 	printbyte = printf("%X%%\n", a);
// 	printf("\npb:%d\n", printbyte);
// 	return (0);
// }
