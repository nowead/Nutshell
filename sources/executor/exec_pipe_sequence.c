/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:08:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 18:56:22 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// curr->sym == PIPE_SEQUENCE
int	exec_pipe_sequence(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (!is_there_pipe(curr))
		return (single_command(curr->child[0], shell_ctx));
	else
		return (multiple_command(curr, shell_ctx));
}
