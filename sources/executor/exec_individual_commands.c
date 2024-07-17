/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_individual_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:30:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/17 22:56:51 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
{
	pid_t			pid;

	if (pipe_redirect_first(fd))
		return (-1);
	if (exec_redirect_only(curr, shell_ctx) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			return (-1);
		return (-1);
	}
	if (pid == 0)
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			err_exit("close", 1, 1);
		convert_to_child_process();
		exec_command(curr, shell_ctx);
	}
	if (restore_stdfd(shell_ctx))
		return (-1);
	return (0);
}

int	middle_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
{
	pid_t			pid;

	if (pipe_redirect_middle(fd))
		return (-1);
	if (exec_redirect_only(curr, shell_ctx))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			return (-1);
		return (-1);
	}
	if (pid == 0)
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			err_exit("close", 1, 1);
		convert_to_child_process();
		exec_command(curr, shell_ctx);
	}
	if (restore_stdfd(shell_ctx))
		return (-1);
	return (0);
}

int	last_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx, \
int *is_signaled)
{
	pid_t			pid;

	if (pipe_redirect_last(fd))
		return (-1);
	if (exec_redirect_only(curr, shell_ctx))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		convert_to_child_process();
		exec_command(curr, shell_ctx);
	}
	signal(SIGINT, SIG_IGN);
	if (save_exit_status(pid, shell_ctx, is_signaled) == -1)
		return (-1);
	if (restore_stdfd(shell_ctx))
		return (-1);
	return (0);
}

int	save_exit_status(pid_t pid, t_shell_ctx *shell_ctx, int *is_signaled)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	shell_ctx->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			*is_signaled = 1;
	}
	return (0);
}
