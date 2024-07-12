/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:33:02 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 16:03:55 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_return(int ret_val, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ft_dprintf(STDERR_FILENO, format, args);
	va_end(args);
	return (ret_val);
}
