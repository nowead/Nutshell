/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_affixes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:03:02 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 14:49:04 by seonseo          ###   ########.fr       */
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

void	exec_cmd_suffix_argument(t_ast_node *curr, char **argv, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->token && curr->child[0]->token->type == TOK_WORD)
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

int	exec_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == IO_FILE)
	{
		if (exec_io_file(curr->child[0]))
			return (-1);
	}
	else
	{
		if (exec_io_here(curr->child[0], shell_ctx))
			return (-1);
	}
	return (0);
}
