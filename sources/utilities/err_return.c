/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:33:02 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 16:18:24 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_return(int ret_val, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ft_dprintf(STDERR_FILENO, format, args);
	ft_dprintf(STDERR_FILENO, ": %s\n", strerror(errno));
	va_end(args);
	return (ret_val);
}
