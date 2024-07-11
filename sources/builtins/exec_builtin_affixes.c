/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_affixes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:29:43 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 01:42:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (exec_builtin_io_redirect(curr->child[0], shell_ctx) == -1)
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_builtin_cmd_suffix(t_ast_node *curr, char **argv, \
t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
		{
			if (exec_builtin_io_redirect(curr->child[0], shell_ctx) == -1)
				return (-1);
		}
		else if (curr->child[0]->token->type == TOK_WORD)
			add_argument(argv, curr->child[0]->token->str);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_builtin_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == IO_FILE)
		return (exec_builtin_io_file(curr->child[0]));
	else
		return (exec_builtin_io_here(curr->child[0], shell_ctx->envp));
}
