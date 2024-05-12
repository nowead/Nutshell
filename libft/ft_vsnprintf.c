/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:13:00 by macbookair        #+#    #+#             */
/*   Updated: 2024/04/22 13:56:40 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list args)
{
	size_t	i;
	ssize_t	printbyte;
	size_t	total_printbyte;
	t_str	dst;

	if (0 != size)
		*str = '\0';
	dst.str = str;
	dst.size = size;
	total_printbyte = 0;
	i = 0;
	while (format[i])
	{
		if ('%' == format[i])
			printbyte = ft_snprintf_print_format_string(&dst, format, args, &i);
		else
			printbyte = ft_snprintf_print_plain_string(&dst, format, &i);
		if (-1 == printbyte)
			break ;
		total_printbyte += printbyte;
	}
	if (-1 == printbyte)
		return (-1);
	return (total_printbyte);
}
