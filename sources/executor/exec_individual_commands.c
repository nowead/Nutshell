/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_individual_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:30:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 18:40:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
// {
// 	pid_t			pid;

// 	if (pipe(fd) == -1)
// 		return (-1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	if (pid == 0)
// 	{
// 		set_echoctl(NULL, ECHOCTL_ON);
// 		signal(SIGINT, SIG_DFL);
// 		if (dup2(fd[1], STDOUT_FILENO) == -1)
// 			err_exit("dup2", 1, EXIT_FAILURE);
// 		if (close(fd[0]) == -1 || close(fd[1]) == -1)
// 			err_exit("close", 1, EXIT_FAILURE);
// 		exec_command(curr, shell_ctx);
// 	}
// 	return (0);
// }

int	backup_stdfd(t_shell_ctx *shell_ctx)
{
	shell_ctx->stdfd[0] = dup(STDIN_FILENO);
	shell_ctx->stdfd[1] = dup(STDOUT_FILENO);
	if (shell_ctx->stdfd[0] == -1 || shell_ctx->stdfd[1] == -1)
		return (-1);
	return (0);
}

int	restore_stdfd(t_shell_ctx *shell_ctx)
{
	if (dup2(shell_ctx->stdfd[0], STDIN_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (dup2(shell_ctx->stdfd[1], STDOUT_FILENO) == -1)
		return (err_return(-1, "dup2"));
	return (0);
}

int	is_there_here_doc(t_ast_node *curr)
{
	int	i;

	if (curr->sym == IO_HERE)
		return (1);
	i = 0;
	if (curr->child)
	{
		while (i < curr->child_num)
		{
			if (is_there_here_doc(curr->child[i++]))
				return (1);
		}
	}
	return (0);
}

int	pipe_redirect_first(int fd[3], t_shell_ctx *shell_ctx)
{
	if (pipe(fd) == -1)
		return (err_return(-1, "pipe"));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (err_return(-1, "dup2"));
	return (0);
}

int	first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
{
	pid_t			pid;

	if (pipe_redirect_first(fd, shell_ctx))
		return (-1);
	if (is_there_here_doc(curr) && exec_redirect_only(curr, shell_ctx) == -1)
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
		set_echoctl(NULL, ECHOCTL_ON);
		signal(SIGINT, SIG_DFL);
		exec_command(curr, shell_ctx);
	}
	if (restore_stdfd(shell_ctx))
		return (-1);
	return (0);
}

int	pipe_redirect_middle(int fd[3], t_shell_ctx *shell_ctx)
{
	if (close(fd[1]) == -1)
		return (-1);
	fd[2] = fd[0];
	if (pipe(fd) == -1)
		return (-1);
	if (dup2(fd[2], STDIN_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (close(fd[2]) == -1)
		return (err_return(-1, "close_pipe_redirect_middle"));
	return (0);
}

int	middle_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
{
	pid_t			pid;

	if (pipe_redirect_middle(fd, shell_ctx))
		return (-1);
	if (is_there_here_doc(curr) && exec_redirect_only(curr, shell_ctx))
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
		signal(SIGINT, SIG_DFL);
		exec_command(curr, shell_ctx);
	}
	if (restore_stdfd(shell_ctx))
		return (-1);
	return (0);
}

int	pipe_redirect_last(int fd[3], t_shell_ctx *shell_ctx)
{
	if (close(fd[1]) == -1)
		return (err_return(-1, "close_pipe_redirect_last"));
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (close(fd[0]) == -1)
		return (err_return(-1, "close_pipe_redirect_last"));
	return (0);
}

int	last_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx, \
int *is_signaled)
{
	pid_t			pid;

	if (pipe_redirect_last(fd, shell_ctx))
		return (-1);
	if (is_there_here_doc(curr) && exec_redirect_only(curr, shell_ctx))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		exec_command(curr, shell_ctx);
	}
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
