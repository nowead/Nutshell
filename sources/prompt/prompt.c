/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/06/20 17:07:51 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_SIGNAL
#define USE_READLINE
#include "minishell.h"

int	sigint_flag = 0;

void	ast_clear(t_ast	*ast)
{
	// ft_printf("\n\n");
	// print_ast(ast->root, 0);
	// ft_printf("\n\n");
	tokenlist_clear(ast->tokenlist);
	clear_ast(ast->root);
	free(ast);
}

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
	char			*line;
	char			*old_line;
	char			*new_line;
	char			*join;
	struct termios	old_term;
	t_ast			*ast;
	int				incomplete_cmd;

	set_echoctl(&old_term);
	incomplete_cmd = 0;
    while(1)
	{
		if (!incomplete_cmd)
			printf("Nutshell $ \033[s\b\b\b\b\b\b\b\b\b\b\b");
		line = readline(get_prompt(incomplete_cmd));
		if (!line)
		{
			if (incomplete_cmd)
			{
				incomplete_cmd = 0;
				continue;
			}
			exit_prompt(&old_term);
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
			old_line = line;
			continue;
		}
		ctrl_cmd(ast);
		ast_clear(ast);
		add_history(line);
		free(line);
    }
	return (0);
}

char				*line;
char				*new_line;
char				*join;
struct termios	old_term;
t_ast			*ast;
int				incomplete_cmd;

	set_echoctl(&old_term);
    while(1)
	{
		set_signal(1);
		printf("Nutshell $ \033[s\b\b\b\b\b\b\b\b\b\b\b");
		line = readline("Nutshell $ ");
        if (!line)
			exit_prompt();
		while (1)
		{
			set_signal(2);
			incomplete_cmd = 0;
			ast = parse(line, &incomplete_cmd);
			if (incomplete_cmd)
			{
				printf("> \033[s\b\b");
				new_line = readline("> ");
				if (sigint_flag)
				{
					printf("sigint is recieved\n");
					sigint_flag = 0;
					if (new_line)
						free(new_line);
					break ;
				}
				if (!new_line)
				{
					printf("\033[u\033[1B\033[1A");
					break ;
				}
				join = ft_strjoin(line, new_line);
				free(line);
				free(new_line);
				if (join == NULL)
					break;
				line = join;
			}
			else
				break;
		}
		if (incomplete_cmd)
		{
			if (line != NULL)
				free(line);
			continue ;
		}
		if (ast != NULL)
			ctrl_cmd(ast);
		if (ast != NULL)
			ast_clear(ast);
		add_history(line);
		free(line);
    }
	restore_echoctl(&old_term);
	return (0);
}
