/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:02:45 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 13:12:09 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_redirect_first(int fd[3])
{
	if (pipe(fd) == -1)
		return (err_return(-1, "pipe"));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (err_return(-1, "dup2"));
	return (0);
}

int	pipe_redirect_middle(int fd[3])
{
	if (close(fd[1]) == -1)
		return (-1);
	fd[2] = fd[0];
	if (pipe(fd) == -1)
		return (-1);
	if (dup2(fd[2], STDIN_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (close(fd[2]) == -1)
		return (err_return(-1, "close"));
	return (0);
}

int	pipe_redirect_last(int fd[3])
{
	if (close(fd[1]) == -1)
		return (err_return(-1, "close"));
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (close(fd[0]) == -1)
		return (err_return(-1, "close"));
	return (0);
}
