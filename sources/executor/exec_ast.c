/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/07/17 20:58:44 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ast(t_ast *ast, t_shell_ctx *shell_ctx)
{
	shell_ctx->exit_status = 0;
	exec_and_or(ast->root, shell_ctx);
}
