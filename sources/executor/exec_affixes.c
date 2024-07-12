/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_affixes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:03:02 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 17:16:16 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			exec_io_redirect(curr->child[0], shell_ctx);
		curr = curr->child[1];
	}
}

void	exec_cmd_suffix(t_ast_node *curr, char **argv, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			exec_io_redirect(curr->child[0], shell_ctx);
		else if (curr->child[0]->token->type == TOK_WORD)
			add_argument(argv, curr->child[0]->token->str);
		curr = curr->child[1];
	}
}

void	add_argument(char **argv, char *arg)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	argv[i] = ft_strdup(arg);
	if (argv[i] == NULL)
		err_exit("add_argument", 1, EXIT_FAILURE);
}

void	exec_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == IO_FILE)
		exec_io_file(curr->child[0]);
	else
		exec_io_here(curr->child[0], shell_ctx);
}
