/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:41:08 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 21:41:25 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concatenate_str(char *old_str, char *str)
{
	char	*new_str;

	new_str = ft_strjoin(old_str, str);
	free(old_str);
	free(str);
	if (new_str == NULL)
	{
		perror("ft_strjoin");
		return (NULL);
	}
	return (new_str);
}
