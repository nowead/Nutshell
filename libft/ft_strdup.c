/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:44:02 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/04 15:03:39 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str_dup;

	size = ft_strlen(s1) + 1;
	str_dup = (char *)malloc(sizeof(char) * size);
	if (str_dup == NULL)
		return (NULL);
	ft_strlcpy(str_dup, s1, size);
	return (str_dup);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	// char	str[3] = {'a', 'b', 'c'};
// 	// char	str1[] = "bare";
// 	// char	*str_dup;
// 	// char	*str_dup1;

// 	// str_dup = ft_strdup(str);
// 	// str_dup1 = strdup(str);
// 	// printf("ft_strdup: %s\n", str_dup);
// 	// printf("len: %lu\n", strlen(str_dup));
// 	// printf("strdup: %s\n", str_dup1);
// 	// printf("len: %lu\n", strlen(str_dup1));
// 	// printf("\n");
// 	// str_dup = ft_strdup(str1);
// 	// str_dup1 = strdup(str1);
// 	// printf("ft_strdup: %s\n", str_dup);
// 	// printf("len: %lu\n", strlen(str_dup));
// 	// printf("strdup: %s\n", str_dup1);
// 	// printf("len: %lu\n", strlen(str_dup1));
// }
