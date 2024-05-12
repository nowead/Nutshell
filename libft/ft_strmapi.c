/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:12:17 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/04 18:01:54 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	slen;
	char			*s1;

	if (s == NULL)
		return (ft_strdup(""));
	if (f == NULL)
		return (ft_strdup(s));
	slen = ft_strlen(s);
	s1 = (char *)malloc(sizeof(char) * (slen + 1));
	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		s1[i] = f(i, s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

// #include <stdio.h>

// char	f(unsigned int i, char c)
// {
// 	if (i > 5 && 'a' <= c && c <= 'z')
// 		return (c - 'a' + 'A');
// 	return (c);
// }

// int	main(void)
// {
// 	char	s[] = "mama mia! gaous";

// 	printf("%s\n", ft_strmapi(s, f));
// }
