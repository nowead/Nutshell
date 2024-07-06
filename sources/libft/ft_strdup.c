/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:44:02 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/06 20:19:11 by seonseo          ###   ########.fr       */
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
