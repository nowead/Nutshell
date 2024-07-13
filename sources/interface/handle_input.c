/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:22:40 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 21:40:55 by seonseo          ###   ########.fr       */
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
		exit_shell(&(shell_ctx->old_term));
	else
	{
		*incomplete_cmd = 0;
		ft_dprintf(2, "\033[u\033[1B\033[1A");
		ft_dprintf(2, "nutshell: syntax error: unexpected end of file\n");
	}
}

void	exit_shell(struct termios *old_term)
{
	printf("\033[u\033[1B\033[1A");
	printf("exit\n");
	restore_echoctl(old_term);
	exit(-1);
}
