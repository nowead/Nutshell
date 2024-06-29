/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlncat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:31:57 by seonseo           #+#    #+#             */
/*   Updated: 2024/04/22 13:40:59 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlncat(char *dst, const char *src, size_t dstsize, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && i + 1 < dstsize)
	{
		i++;
	}
	j = 0;
	while (src[j] && i + 1 < dstsize && j < n)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	while (src[j] && j < n)
		j++;
	return (j);
}
