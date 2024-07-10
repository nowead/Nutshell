/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:08:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/10 20:15:58 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe_sequence(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (!is_there_pipe(curr))
		return (single_command(curr->child[0], shell_ctx));
	else
		return (multiple_command(curr, shell_ctx));
}

int	single_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (is_builtin_cmd(curr->child[0]))
		return (exec_builtin_simple_command(curr->child[0], shell_ctx));
	return (exec_external_cmd(curr, shell_ctx));
}

int	exec_external_cmd(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_echoctl(NULL, ECHOCTL_ON);
		signal(SIGINT, SIG_DFL);
		exec_command(curr, shell_ctx);
	}
	signal(SIGINT, SIG_IGN);
	if (wait(&status) == -1)
		return (-1);
	shell_ctx->exit_status = WEXITSTATUS(status);
	if (WEXITSTATUS(status) == 2)
		printf("\n");
	set_echoctl(NULL, ECHOCTL_OFF);
	set_signal_handler(SIGINT_HANDLER);
	return (0);
}
