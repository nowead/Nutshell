/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:07:25 by seonseo           #+#    #+#             */
/*   Updated: 2023/10/16 21:18:41 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		return (c - 32);
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
