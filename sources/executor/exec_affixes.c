/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_affixes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:03:02 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/25 22:08:56 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (exec_io_redirect(curr->child[0], shell_ctx))
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_cmd_suffix_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (exec_io_redirect(curr->child[0], shell_ctx))
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

void	exec_cmd_suffix_argument(t_ast_node *curr, char **argv)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == TERMINAL)
			add_argument_from_tokenlist(argv, curr->child[0]->tokenlist);
		curr = curr->child[1];
	}
}

int	exec_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == IO_FILE)
	{
		if (exec_io_file(curr->child[0]))
			return (-1);
	}
	else
	{
		if (exec_io_here(shell_ctx))
			return (-1);
	}
	return (0);
}
