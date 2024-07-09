/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:04:19 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/10 04:04:37 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redirect_list(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child == NULL)
		return ;
	exec_io_redirect(curr->child[0], shell_ctx);
	exec_redirect_list(curr->child[1], shell_ctx);
}

void	exec_subshell(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (exec_and_or(curr, shell_ctx) == -1)
	{
		perror("subshell");
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}
