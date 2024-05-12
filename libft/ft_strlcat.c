/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:27:56 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/02 18:36:53 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *dst, size_t dstsize)
{
	size_t	dstlen;

	dstlen = 0;
	while (dst[dstlen] && dstlen < dstsize)
		dstlen++;
	return (dstlen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strnlen(dst, dstsize);
	srclen = ft_strlen(src);
	if (dstlen + 1 < dstsize)
		ft_strlcpy(dst + dstlen, src, dstsize - dstlen);
	return (dstlen + srclen);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char			dest[42] = "apple";
	char			src[] = "pie";
	size_t			len;
	
	len = ft_strlcat(dest, src, 7);
	printf("%s %zu\n", dest, len);
	return 0;
}
*/

// #include <stdio.h>

// int	main(void)
// {
// 	char arr[50];

// 	for (int i = 0; i < 50; ++i)
// 		arr[i] = '#';
// 	arr[0] = '\0';
// 	int len = ft_strlcat(arr, "", 50);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "Hello ", 50);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "World!", 50);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "", 50);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "42", 0);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "42", 3);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "\nHello World!", 20);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "World!", 20);
// 	printf("%s %d\n", arr, len);
// 	len = ft_strlcat(arr, "\nHello World!", 42);
// 	printf("%s %d\n", arr, len);
// 	for (int i = 31; i < 42; ++i)
// 		printf("%d ", arr[i]);
// 	printf("\n");
// 	return 0;
// }
