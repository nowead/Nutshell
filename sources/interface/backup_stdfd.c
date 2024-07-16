/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_stdfd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:59:14 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 20:59:49 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	backup_stdfd(t_shell_ctx *shell_ctx)
{
	shell_ctx->stdfd[0] = dup(STDIN_FILENO);
	shell_ctx->stdfd[1] = dup(STDOUT_FILENO);
	if (shell_ctx->stdfd[0] == -1 || shell_ctx->stdfd[1] == -1)
		return (-1);
	return (0);
}

int	restore_stdfd(t_shell_ctx *shell_ctx)
{
	if (dup2(shell_ctx->stdfd[0], STDIN_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (dup2(shell_ctx->stdfd[1], STDOUT_FILENO) == -1)
		return (err_return(-1, "dup2"));
	return (0);
}
