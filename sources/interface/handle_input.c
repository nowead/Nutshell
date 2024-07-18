/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:22:40 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 15:20:16 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_shell_ctx *shell_ctx, char **line)
{
	if (g_sigint_flag == 1)
	{
		shell_ctx->exit_status = 1;
		g_sigint_flag = 0;
	}
	if (*line == NULL)
		exit_shell(shell_ctx);
	return (0);
}

void	exit_shell(t_shell_ctx *shell_ctx)
{
	if (printf("exit\n") == -1)
		err_exit("printf", 1, EXIT_FAILURE);
	restore_stdfd(shell_ctx);
	restore_echoctl(&(shell_ctx->old_term), STDIN_FILENO);
	exit(0);
}
