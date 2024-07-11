/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:58:30 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/11 17:27:50 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	int				fd[3];
	size_t			cmd_cnt;
	int				status;

	signal(SIGINT, SIG_IGN);
	if (first_command(curr->child[0], fd, shell_ctx) == -1)
		return (-1);
	cmd_cnt = 1;
	curr = curr->child[1];
	if (execute_middle_commands(&curr, fd, &cmd_cnt, shell_ctx))
		return (-1);
	if (last_command(curr->child[0], fd, shell_ctx) == -1)
		return (-1);
	cmd_cnt++;
	if (wait_for_all_commands(cmd_cnt, &status))
		return (-1);
	shell_ctx->exit_status = WEXITSTATUS(status);
	if (WEXITSTATUS(status) == 2)
		printf("\n");
	set_echoctl(NULL, ECHOCTL_OFF);
	set_signal_handler(SIGINT_HANDLER);
	return (0);
}

int	execute_middle_commands(t_ast_node **curr, int fd[3], \
size_t *cmd_cnt, t_shell_ctx *shell_ctx)
{
	while (is_there_pipe(*curr))
	{
		if (middle_command((*curr)->child[0], fd, shell_ctx) == -1)
			return (-1);
		(*cmd_cnt)++;
		*curr = (*curr)->child[1];
	}
	return (0);
}

int	wait_for_all_commands(size_t cmd_cnt, int *status)
{
	while (cmd_cnt)
	{
		if (wait(status) == -1)
			return (-1);
		cmd_cnt--;
	}
	return (0);
}

int	is_there_pipe(t_ast_node *curr)
{
	if (curr->child[1]->child)
		return (1);
	else
		return (0);
}
