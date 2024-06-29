/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:13:32 by seonseo           #+#    #+#             */
/*   Updated: 2023/10/16 21:18:11 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%c\n", ft_tolower('C'));
	printf("%c\n", ft_tolower('a'));
	printf("%c\n", ft_tolower('^'));
}
*/
