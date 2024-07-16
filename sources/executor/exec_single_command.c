/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:13:41 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 13:04:26 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (backup_stdfd(shell_ctx))
		return (-1);
	if (is_there_here_doc(curr) && exec_redirect_only(curr, shell_ctx))
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
	handle_signal(curr, shell_ctx, WTERMSIG(status)) == 0)
		return (-1);
	if (restore_stdfd(shell_ctx) == -1)
		return (-1);
	set_echoctl(NULL, ECHOCTL_OFF);
	set_signal_handler(SIGINT_HANDLER);
	return (shell_ctx->exit_status);
}
