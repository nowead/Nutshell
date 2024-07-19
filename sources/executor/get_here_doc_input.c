/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:07:42 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/19 13:34:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (get_here_doc_input_from_pipe(curr->child[0], shell_ctx))
		{
			signal(SIGINT, sigint_handler);
			shell_ctx->exit_status = 1;
			return (-1);
		}
		curr = curr->child[1];
	}
	signal(SIGINT, sigint_handler);
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
