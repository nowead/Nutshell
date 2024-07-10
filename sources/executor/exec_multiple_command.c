/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:58:30 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/10 19:00:48 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	int				fd[3];
	size_t			cmd_cnt;
	int				status;
	struct termios	old_term;

	signal(SIGINT, SIG_IGN);
	if (first_command(curr->child[0], fd, shell_ctx) == -1)
		return (-1);
	cmd_cnt = 1;
	curr = curr->child[1];
	while (is_there_pipe(curr))
	{
		if (middle_command(curr->child[0], fd, shell_ctx) == -1)
			return (-1);
		cmd_cnt++;
		curr = curr->child[1];
	}
	if (last_command(curr->child[0], fd, shell_ctx) == -1)
		return (-1);
	cmd_cnt++;
	while (cmd_cnt)
	{
		if (wait(&status) == -1)
			return (-1);
		cmd_cnt--;
	}
	shell_ctx->exit_status = WEXITSTATUS(status);
	if (WEXITSTATUS(status) == 2)
		printf("\n");
	set_echoctl(&old_term, ECHOCTL_OFF);
	set_signal_handler(SIGINT_HANDLER);
	return (0);
}

int	is_there_pipe(t_ast_node *curr)
{
	if (curr->child[1]->child)
		return (1);
	else
		return (0);
}

int	first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
{
	pid_t			pid;
	struct termios	old_term;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_echoctl(&old_term, ECHOCTL_ON);
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
	struct termios	old_term;

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
	if (close(fd[2]) == -1)
		return (-1);
	return (0);
}

int	last_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx)
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
	if (close(fd[0]) == -1)
		return (-1);
	return (0);
}
