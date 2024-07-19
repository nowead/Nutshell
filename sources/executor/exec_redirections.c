/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:25:00 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/19 13:29:04 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sym : command
int	exec_redirections(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (redirect_only_simple_command(curr, shell_ctx))
	{
		shell_ctx->exit_status = 1;
		return (-1);
	}
	return (0);
}

// command : command
int	redirect_only_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		curr = curr->child[0];
	if (curr->child[0]->sym == SUBSHELL)
	{
		if (exec_redirect_list(curr->child[1], shell_ctx))
			return (-1);
		return (0);
	}
	if (curr->child_num == 2)
	{
		if (exec_cmd_suffix_redirect(curr->child[1], shell_ctx))
			return (-1);
	}
	else if (curr->child_num == 3)
	{
		if (exec_cmd_prefix(curr->child[0], shell_ctx))
			return (-1);
		if (exec_cmd_suffix_redirect(curr->child[2], shell_ctx))
			return (-1);
	}
	else
		if (exec_cmd_prefix(curr->child[0], shell_ctx))
			return (-1);
	return (0);
}
