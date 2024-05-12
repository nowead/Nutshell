/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:33:39 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/02 18:44:28 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fillnbr(char *nbr_str, int nbrlen, long long n)
{
	nbr_str[nbrlen] = '\0';
	nbrlen--;
	if (n == 0)
	{
		nbr_str[0] = '0';
		return ;
	}
	if (n < 0)
	{
		nbr_str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		nbr_str[nbrlen] = n % 10 + '0';
		n /= 10;
		nbrlen--;
	}
}

static int	ft_nbrlen(int n)
{
	int	len;

	if (n == -2147483648)
		return (11);
	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*nbr_str;
	int		nbrlen;

	nbrlen = ft_nbrlen(n);
	nbr_str = (char *)malloc(sizeof(char) * (nbrlen + 1));
	if (nbr_str == NULL)
		return (NULL);
	ft_fillnbr(nbr_str, nbrlen, n);
	return (nbr_str);
}
// #include <stdio.h>
// #include <limits.h>

// int	main(void)
// {
// 	printf("\"%s\"\n", ft_itoa(-2147483648LL));
// }
