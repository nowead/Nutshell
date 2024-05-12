/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:13:00 by macbookair        #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	size_t	i;
	ssize_t	printbyte;
	size_t	total_printbyte;

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
	if (-1 == printbyte)
		return (-1);
	return (total_printbyte);
}
