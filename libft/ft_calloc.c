/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:44:09 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/07 14:18:27 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	if (count * size == 0)
		ft_bzero(mem, 1);
	else
		ft_bzero(mem, count * size);
	return (mem);
}
/*
#include <stdio.h>

int main(void)
{
	char	str[] = "I will be pirate king";
	char	*ptr;

	ptr = (char *)calloc(22, 1);
	ft_strlcpy(ptr, str, 22);
	printf("%s\n", ptr);
}
*/
