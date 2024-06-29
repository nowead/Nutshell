/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:41:25 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/09 11:04:47 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_printlst(t_list *lst)
{
	size_t	size;

	if (lst == NULL)
		return (0);
	size = 0;
	while (lst->content)
	{
		ft_putstr_fd(lst->content, 1);
		(lst->content)++;
		size++;
	}
	return (size);
}
