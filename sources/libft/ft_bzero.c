/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:26:09 by seonseo           #+#    #+#             */
/*   Updated: 2023/10/20 11:39:30 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	unsigned char str[42] = {"00000000000000000000"};

	printf("%s\n", str);
	ft_bzero(str + 3, 10);
	printf("%s\n", str);
	return (0);
}
*/
