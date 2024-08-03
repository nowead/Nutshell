/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:04:19 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/04 02:55:21 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect_list(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child == NULL)
		return (0);
	if (exec_io_redirect(curr->child[0], shell_ctx))
		return (-1);
	if (exec_redirect_list(curr->child[1], shell_ctx))
		return (-1);
	return (0);
}

void	exec_subshell(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (exec_and_or(curr->child[0], shell_ctx) == -1)
	{
		if (shell_ctx->exit_status == 0)
			shell_ctx->exit_status = 1;
		exit (shell_ctx->exit_status);
	}
	else
		exit(shell_ctx->exit_status);
}
