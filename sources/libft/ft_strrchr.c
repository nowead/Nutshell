/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:30:29 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/06 20:19:50 by seonseo          ###   ########.fr       */
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
