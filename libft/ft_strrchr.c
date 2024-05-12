/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:30:29 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/07 18:38:51 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*lastchr;

	lastchr = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			lastchr = (char *)s + i;
		i++;
	}
	if ('\0' == (char)c)
		return ((char *)s + i);
	return (lastchr);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	str[] = "ontopoftheworld";

// 	char s[] = "tripouille";
// 	char s2[] = "ltripouiel";
// 	char s3[] = "";

// 	printf("%s\n", ft_strrchr(str, 'p'));
// 	printf("%s\n", ft_strrchr(s, 't' + 256));
// 	printf("%s\n", strrchr(s, 't' + 256));
// 	printf("%d\n", (char)256);
// }
