/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:18:05 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/01 19:43:34 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_strtol_determine_base(const char *str, int *base)
{
	if (*base == 0)
	{
		if (*str == '0')
		{
			str++;
			if (*str == 'x' || *str == 'X')
			{
				str++;
				*base = 16;
			}
			else
				*base = 8;
		}
		else
			*base = 10;
	}
	else if (*base == 16)
	{
		if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
			str += 2;
	}
	return (str);
}

static int	char_to_digit(char c, int base)
{
	int	digit;

	if (ft_isdigit(c))
		digit = c - '0';
	else if (ft_isalpha(c))
		digit = ft_toupper(c) - 'A' + 10;
	else
		digit = -1;
	if (digit >= base)
		digit = -1;
	return (digit);
}

static int	check_overflow(long *result, int base, int *sign, int digit)
{
	if (*result < 0 || (*result > LONG_MAX / base) || \
	((*result == LONG_MAX / base) && \
	(digit > LONG_MAX % base)))
	{
		if (*result < 0)
			errno = ERANGE;
		else if (*sign == 1)
		{
			*result = LONG_MAX;
			errno = ERANGE;
		}
		else
		{
			*result = -LONG_MAX - 1L;
			*sign = 1;
			if ((*result > LONG_MAX / base) || \
			((*result == LONG_MAX / base) && \
			(digit > LONG_MAX % base + 1)))
				errno = ERANGE;
		}
		return (0);
	}
	return (1);
}

static long	ft_strtol_convert_to_number(const char *str, int base, int sign, \
char **endptr)
{
	long		result;
	int			digit;
	const char	*str_start;

	str_start = str;
	result = 0;
	while (*str)
	{
		digit = char_to_digit(*str, base);
		if (digit == -1)
			break ;
		if (check_overflow(&result, base, &sign, digit))
			result = result * base + digit;
		str++;
	}
	if (endptr)
		*endptr = (char *)str;
	if (str == str_start)
		errno = EINVAL;
	return (result * sign);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	const char	*str_start;
	int			sign;
	long		result;

	str_start = str;
	str = ft_strtol_skip_whitespace(str);
	str = ft_strtol_handle_sign(str, &sign);
	str = ft_strtol_determine_base(str, &base);
	result = ft_strtol_convert_to_number(str, base, sign, endptr);
	if (errno == EINVAL)
		*endptr = (char *)str_start;
	return (result);
}
