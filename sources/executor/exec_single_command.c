/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:13:41 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/17 18:56:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// curr->sym == COMMAND
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

	if (exec_redirect_only(curr, shell_ctx))
		return (-1);
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
	if (WIFSIGNALED(status) && \
	handle_signal(shell_ctx, WTERMSIG(status)) == 0)
		return (-1);
	set_echoctl(NULL, ECHOCTL_OFF);
	signal(SIGINT, sigint_handler);
	return (shell_ctx->exit_status);
}
