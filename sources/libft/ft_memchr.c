/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:24:37 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/07 15:53:48 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

	// #include <stdio.h>
	// #include <string.h>

	// int	main(void)
	// {
	// 	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};

	// 	printf("%s\n", (char *)ft_memchr(tab, -1, 7));
	// 	printf("%s\n", (char *)memchr(tab, -1, 7));
	// }
