/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_affixes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:29:43 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 21:27:16 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			exec_builtin_io_redirect(curr->child[0], shell_ctx);
		curr = curr->child[1];
	}
}

// int	exec_builtin_cmd_suffix(t_ast_node *curr, char **argv, \
// t_shell_ctx *shell_ctx)
// {
// 	while (curr->child)
// 	{
// 		if (curr->child[0]->sym == IO_REDIRECT)
// 		{
// 			if (exec_builtin_io_redirect(curr->child[0], shell_ctx) == -1)
// 				return (-1);
// 		}
// 		else if (curr->child[0]->token->type == TOK_WORD)
// 			add_argument(argv, curr->child[0]->token->str);
// 		curr = curr->child[1];
// 	}
// 	return (0);
// }

void	exec_redirect_in_suffix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			exec_builtin_io_redirect(curr->child[0], shell_ctx);
		curr = curr->child[1];
	}
}

int	exec_suffix_without_redirect(t_ast_node *curr, char **argv, \
t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->token && curr->child[0]->token->type == TOK_WORD)
			add_argument(argv, curr->child[0]->token->str);
		curr = curr->child[1];
	}
	return (0);
}

void	exec_builtin_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == IO_FILE)
		exec_builtin_io_file(curr->child[0]);
	else
		exec_builtin_io_here(curr->child[0], shell_ctx);
}
