/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/06/07 19:33:46 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_end()
{
	pid_t	pid;
	char	*line;

	line = "none";
	pid = fork();
	if (pid == 1)
		err_ctrl("fork fail ", 1, EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
	}
}