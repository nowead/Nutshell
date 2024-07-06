/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:52:53 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/01 18:53:55 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		if (ft_printf("%s\n", strs[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
