/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/06/24 15:46:21 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_SIGNAL
#define USE_READLINE
#include "minishell.h"

int	sigint_flag = 0;

void	exit_prompt(struct termios *old_term)
{
	printf("\033[u\033[1B\033[1A");
	printf("exit\n");
	restore_echoctl(old_term);
	exit(-1);
}

const char *get_prompt(int incomplete_cmd)
{
	if (incomplete_cmd)
		return ("> ");
	else
		return ("Nutshell $ ");
}

int	prompt(void)
{
	struct termios	old_term;
	char			*line;
	char			*old_line;
	char			*new_line;
	t_ast			*ast;
	int				incomplete_cmd;

	set_echoctl(&old_term);
	incomplete_cmd = 0;
	set_signal(SIGINT_HANDLER);
    while(1)
	{
		if (!incomplete_cmd)
			printf("Nutshell $ \033[s\b\b\b\b\b\b\b\b\b\b\b");
		else
			printf("> \033[s\b\b");
		line = readline(get_prompt(incomplete_cmd));
		if (sigint_flag == 1)
		{
			set_signal(SIGINT_HANDLER);
			incomplete_cmd = 0;
			sigint_flag = 0;
		}
		if (!line)
		{
			if (!incomplete_cmd)
				exit_prompt(&old_term);
			else
			{
				incomplete_cmd = 0;
				ft_dprintf(2, "\033[u\033[1B\033[1A");
				ft_dprintf(2, "nutshell: syntax error: unexpected end of file\n");
				continue;
			}
		}
		if (!line)
		{
			if (!incomplete_cmd)
				exit_prompt(&old_term);
			else
			{
				incomplete_cmd = 0;
				ft_dprintf(2, "\033[u\033[1B\033[1A");
				ft_dprintf(2, "nutshell: syntax error: unexpected end of file\n");
				continue;
			}
		}
		if (incomplete_cmd)
		{
			new_line = ft_strjoin(old_line, line);
			if (new_line == NULL)
			{
				incomplete_cmd = 0;
				perror("ft_strjoin");
				continue;
			}
			free(old_line);
			free(line);
			line = new_line;
		}
		ast = parse(line, &incomplete_cmd);
		if (incomplete_cmd)
		{
			set_signal(SIGINT_INCOMPLETE_CMD_HANDLER);
			old_line = line;
			continue;
		}
		else
			set_signal(SIGINT_HANDLER);
		if (ast == NULL)
			continue;
		exec_ast(ast);
		clear_ast(ast);
		add_history(line);
		free(line);
    }
	return (0);
}
