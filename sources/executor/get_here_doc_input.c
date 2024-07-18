/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:07:42 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 18:41:04 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sym : pipe_sequence
int	get_here_doc_input(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	struct sigaction	action;

	action.sa_handler = here_doc_handler;
	action.sa_flags = 0;
	action.sa_flags &= ~SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) == -1)
	{
		shell_ctx->exit_status = 1;
		return (err_return(-1, "sigaction"));
	}
	while (curr->child_num)
	{
		if (search_get_heredoc_filename(curr->child[0], shell_ctx) == -1)
		{
			signal(SIGINT, sigint_handler);
			shell_ctx->exit_status = 1;
			return (-1);
		}
		curr = curr -> child[1];
	}
	signal(SIGINT, sigint_handler);
	return (0);
}

int	search_get_heredoc_filename(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		curr = curr->child[0];
	// if (curr->child[0]->sym == SUBSHELL)
	// {
	// 	if (exec_redirect_list(curr->child[1], shell_ctx))
	// 		return (-1);
	// 	return (0);
	// }
	if (curr->child_num == 2)
	{
		if (exec_cmd_suffix_redirect_hd(curr->child[1], shell_ctx))
			return (-1);
	}
	else if (curr->child_num == 3)
	{
		if (exec_cmd_prefix_hd(curr->child[0], shell_ctx))
			return (-1);
		if (exec_cmd_suffix_redirect_hd(curr->child[2], shell_ctx))
			return (-1);
	}
	else
		if (exec_cmd_prefix_hd(curr->child[0], shell_ctx))
			return (-1);
	return (0);
}

int	exec_cmd_prefix_hd(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (exec_io_redirect_hd(curr->child[0], shell_ctx))
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_cmd_suffix_redirect_hd(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (exec_io_redirect_hd(curr->child[0], shell_ctx))
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

// sym : IO_HERE
int	exec_io_redirect_hd(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	*file_name;

	if (curr->child[0]->sym == IO_HERE)
	{
		if (setup_here_doc(curr->child[0], shell_ctx, &file_name))
			return (-1);
		if (add_str_to_strs(file_name, &shell_ctx->heredoc_files))
			return (-1);
	}
	return (0);
}
