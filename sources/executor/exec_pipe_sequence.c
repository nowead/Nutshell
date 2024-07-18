/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:08:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 21:09:23 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe_sequence(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (get_here_doc_input(curr, shell_ctx) == -1)
		return (-1);
	if (!is_there_pipe(curr))
		return (single_command(curr->child[0], shell_ctx));
	else
		return (multiple_command(curr, shell_ctx));
}
