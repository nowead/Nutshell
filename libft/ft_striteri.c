/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:56:55 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/04 18:02:46 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void	ft_f(unsigned int i, char *c)
// {
// 	i++;
// 	if ('a' <= *c && *c <= 'z')
// 		*c = *c - 'a' + 'A';
// }

// int	main(void)
// {
// 	char	str[] = "apple123";

// 	printf("%s\n", str);
// 	ft_striteri(str, ft_f);
// 	printf("%s\n", str);
// }
