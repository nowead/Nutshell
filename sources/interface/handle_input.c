/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:22:40 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/17 14:54:09 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(t_shell_ctx *shell_ctx, int *incomplete_cmd, \
char *old_line, char **line)
{
	if (g_sigint_flag == 1)
		process_sigint_flag(shell_ctx, incomplete_cmd, old_line);
	if (*line == NULL)
	{
		handle_end_of_file(shell_ctx, incomplete_cmd);
		return (1);
	}
	if (*incomplete_cmd)
	{
		*incomplete_cmd = 0;
		*line = concatenate_str(old_line, *line);
		if (*line == NULL)
			return (1);
	}
	return (0);
}

void	process_sigint_flag(t_shell_ctx *shell_ctx, int *incomplete_cmd, \
char *old_line)
{
	if (*incomplete_cmd == 1)
	{
		if (old_line)
			free(old_line);
		set_signal_handler(SIGINT_HANDLER);
		*incomplete_cmd = 0;
	}
	shell_ctx->exit_status = 1;
	g_sigint_flag = 0;
}

void	handle_end_of_file(t_shell_ctx *shell_ctx, int *incomplete_cmd)
{
	if (!*incomplete_cmd)
		exit_shell(shell_ctx);
	else
	{
		*incomplete_cmd = 0;
		set_signal_handler(SIGINT_HANDLER);
		ft_dprintf(2, "Nutshell: syntax error: unexpected end of file\n");
	}
}

void	exit_shell(t_shell_ctx *shell_ctx)
{
	if (printf("exit\n") == -1)
		err_exit("printf", 1, EXIT_FAILURE);
	restore_stdfd(shell_ctx);
	restore_echoctl(&(shell_ctx->old_term));
	exit(0);
}
