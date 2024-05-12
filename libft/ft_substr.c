/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookair <macbookair@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:12:14 by seonseo           #+#    #+#             */
/*   Updated: 2023/12/27 10:52:58 by macbookair       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;

	if (s == NULL || start >= ft_strlen(s))
		return (ft_strdup(""));
	else
	{
		size = ft_strlen(s + start) + 1;
		if (size - 1 > len)
			size = len + 1;
	}
	substr = (char *)malloc(sizeof(char) * size);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, &s[start], size);
	return (substr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*substr;

// 	substr = ft_substr("", 1, 1);
// 	printf("\"%s\"\n", substr);
// }
