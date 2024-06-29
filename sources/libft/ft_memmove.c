/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:32:53 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/07 18:57:47 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (dst <= src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[len - 1 - i] \
			= ((unsigned char *)src)[len - 1 - i];
			i++;
		}
	}
	return (dst);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	unsigned char	board[] = "0123456789abcde";
// 	unsigned char	*dst = NULL;
// 	unsigned char	*src = NULL;

// 	printf("case 1: dst <= src\n");
// 	printf("dst: %s\n", dst);
// 	printf("src: %s\n", src);
// 	printf("length : 6\n");

// 	printf("memmove\n");
// 	memmove(dst, src, 6);
// 	printf("dst: %s\n", dst);
// 	printf("src: %s\n", src);

// 	strcpy((char *)board, "0123456789abcde");
// 	printf("ft_memmove\n");
// 	ft_memmove(dst, src, 6);
// 	printf("dst: %s\n", dst);
// 	printf("src: %s\n", src);

	// strcpy((char *)board, "0123456789abcde");
	// printf("\ncase 2: src > dst\n");
	// dst = board + 3;
	// src = board;
	// printf("dst: %s\n", dst);
	// printf("src: %s\n", src);
	// printf("length : 6\n");

	// printf("memmove\n");
	// memmove(dst, src, 6);
	// printf("dst: %s\n", dst);
	// printf("src: %s\n", src);

	// strcpy((char *)board, "0123456789abcde");
	// printf("ft_memmove\n");
	// ft_memmove(dst, src, 6);
	// printf("dst: %s\n", dst);
	// printf("src: %s\n", src);
	// }
