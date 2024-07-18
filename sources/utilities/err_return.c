/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:33:02 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 13:11:17 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_return(int ret_val, const char *str)
{
	ft_dprintf(STDERR_FILENO, str);
	ft_dprintf(STDERR_FILENO, ": %s\n", strerror(errno));
	return (ret_val);
}
