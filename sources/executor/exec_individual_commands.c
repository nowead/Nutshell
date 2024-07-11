/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_individual_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 21:30:12 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/11 20:58:36 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
{
	pid_t			pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_echoctl(NULL, ECHOCTL_ON);
		signal(SIGINT, SIG_DFL);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_exit("dup2", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			err_exit("close", 1, EXIT_FAILURE);
		exec_command(curr, shell_ctx);
	}
	return (0);
}

int	middle_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
{
	pid_t			pid;

	if (close(fd[1]) == -1)
		return (-1);
	fd[2] = fd[0];
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			return (-1);
		return (-1);
	}
	if (pid == 0)
		middle_command_child(curr, fd, shell_ctx);
	if (close(fd[2]) == -1)
		return (-1);
	return (0);
}

void	middle_command_child(t_ast_node *curr, int fd[3], \
t_shell_ctx *shell_ctx)
{
	signal(SIGINT, SIG_DFL);
	if (dup2(fd[2], STDIN_FILENO) == -1)
		err_exit("dup2", 1, EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		err_exit("dup2", 1, EXIT_FAILURE);
	if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
		err_exit("close", 1, EXIT_FAILURE);
	exec_command(curr, shell_ctx);
}

int	last_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx, \
int *is_signaled)
{
	pid_t			pid;
	struct termios	old_term;

	if (close(fd[1]) == -1)
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
		if (dup2(fd[0], STDIN_FILENO) == -1)
			err_exit("dup2", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1)
			err_exit("close", 1, EXIT_FAILURE);
		exec_command(curr, shell_ctx);
	}
	if (save_exit_status(pid, shell_ctx, is_signaled) == -1)
		return (-1);
	if (close(fd[0]) == -1)
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
