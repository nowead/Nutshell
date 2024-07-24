/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/07/18 17:00:21 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (shell_ctx->exit_status != 258)
// 	shell_ctx->exit_status = 0;
void	exec_ast(t_ast *ast, t_shell_ctx *shell_ctx)
{
	exec_and_or(ast->root, shell_ctx);
}
