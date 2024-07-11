/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:56:58 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/11 22:42:43 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_and_or(t_ast_node *root, t_shell_ctx *shell_ctx)
{
	int	initial_result;

	if (root->child == NULL)
		return (-1);
	initial_result = exec_pipe_sequence(root->child[0], shell_ctx);
	return (exec_and_or_(root->child[1], initial_result, shell_ctx));
}

int	exec_and_or_(t_ast_node *curr, int prev_result, t_shell_ctx *shell_ctx)
{
	int	curr_result;

	if (curr->token && \
	((curr->token->type == TOK_AND_IF && prev_result == 0) || \
	(curr->token->type == TOK_OR_IF && prev_result != 0)))
	{
		curr_result = exec_pipe_sequence(curr->child[0], shell_ctx);
		return (exec_and_or_(curr->child[1], curr_result, shell_ctx));
	}
	return (prev_result);
}
