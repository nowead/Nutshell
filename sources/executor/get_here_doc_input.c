/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:07:42 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/05 18:18:52 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_here_doc_input(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child_num)
	{
		if (get_here_doc_input_from_pipe(curr->child[0], shell_ctx))
		{
			signal(SIGINT, sigint_handler);
			shell_ctx->exit_status = 1;
			return (-1);
		}
		curr = curr->child[1];
	}
	return (0);
}

// sym : pipe_sequence
int	get_here_doc_input_from_pipe(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child_num)
	{
		if (search_make_heredoc_filename(curr->child[0], shell_ctx) == -1)
			return (-1);
		curr = curr->child[1];
	}
	return (0);
}
