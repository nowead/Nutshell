/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_make_heredoc_filename.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:34:08 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/04 02:55:41 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_make_heredoc_filename(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		curr = curr->child[0];
	if (curr->child[0]->sym == SUBSHELL)
	{
		if (get_hd_input_redirect_list(curr->child[1], shell_ctx))
			return (-1);
		return (0);
	}
	if (curr->child_num == 2)
	{
		if (get_hd_input_cmd_suffix(curr->child[1], shell_ctx))
			return (-1);
	}
	else if (curr->child_num == 3)
	{
		if (get_hd_input_cmd_prefix(curr->child[0], shell_ctx))
			return (-1);
		if (get_hd_input_cmd_suffix(curr->child[2], shell_ctx))
			return (-1);
	}
	else
		if (get_hd_input_cmd_prefix(curr->child[0], shell_ctx))
			return (-1);
	return (0);
}

int	get_hd_input_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (get_hd_input_io_redirect(curr->child[0], shell_ctx))
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

int	get_hd_input_cmd_suffix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (get_hd_input_io_redirect(curr->child[0], shell_ctx))
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

// sym : IO_REDIRECT
int	get_hd_input_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	*file_name;

	file_name = NULL;
	if (curr->child[0]->sym == IO_HERE)
	{
		if (make_heredoc_file(curr->child[0], shell_ctx, &file_name))
		{
			if (access(file_name, F_OK) == 0)
				unlink(file_name);
			free(file_name);
			return (-1);
		}
		if (add_str_to_strs(file_name, &shell_ctx->heredoc_files))
			return (-1);
	}
	return (0);
}

int	get_hd_input_redirect_list(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child == NULL)
		return (0);
	if (get_hd_input_io_redirect(curr->child[0], shell_ctx))
		return (-1);
	if (get_hd_input_redirect_list(curr->child[1], shell_ctx))
		return (-1);
	return (0);
}
