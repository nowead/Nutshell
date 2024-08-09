/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:13:41 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/09 17:35:07 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_cmd_signal(t_shell_ctx *shell_ctx, int signaled_status)
{
	if (signaled_status == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit: %d\n", signaled_status);
	else if (signaled_status == SIGINT)
		printf("\n");
	shell_ctx->exit_status = signaled_status + 128;
	convert_to_nutshell_terminal();
	return (0);
}

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

	if (exec_redirections(curr, shell_ctx))
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		convert_to_child_process();
		exec_command(curr, shell_ctx);
	}
	signal(SIGINT, SIG_IGN);
	if (restore_stdfd(shell_ctx))
		return (-1);
	if (wait(&status) == -1)
		return (-1);
	shell_ctx->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && \
	handle_single_cmd_signal(shell_ctx, WTERMSIG(status)) == 0)
		return (-1);
	convert_to_nutshell_terminal();
	return (shell_ctx->exit_status);
}
