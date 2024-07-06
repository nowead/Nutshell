/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:27:56 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/06 20:19:26 by seonseo          ###   ########.fr       */
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
