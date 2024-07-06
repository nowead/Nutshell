/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_ctrl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:01:34 by damin             #+#    #+#             */
/*   Updated: 2024/07/06 20:35:45 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_exit(char *err, int sys, int exit_status)
{
	if (!sys)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	exit(exit_status);
}
