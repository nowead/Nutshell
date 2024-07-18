/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str_to_strs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:42:10 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 17:49:11 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_str_to_strs(char *str, char ***strs)
{
	char	**new_strs;

	if (!*strs)
	{
		new_strs = (char **)ft_calloc(2, sizeof(char *));
		if (!new_strs)
			return (err_return(-1, "malloc"));
		new_strs[0] = str;
	}
	else
	{
		new_strs = (char **)ft_calloc((ft_strslen(*strs) + 2), sizeof(char *));
		if (!new_strs)
			return (err_return(-1, "malloc"));
		ft_memcpy(new_strs, *strs, sizeof(char *) * ft_strslen(*strs));
		new_strs[ft_strslen(*strs)] = str;
	}
	free(*strs);
	*strs = new_strs;
	return (0);
}
