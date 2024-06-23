/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:01:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/07 19:02:39 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_ctrl(char *err, int sys, int exit_status)
{
	if (!sys)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	exit(exit_status);
}