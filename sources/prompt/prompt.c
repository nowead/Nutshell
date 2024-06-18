/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/06/18 17:22:09 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_SIGNAL
#define USE_READLINE
#include "minishell.h"

void	ast_clear(t_ast	*ast)
{
	// ft_printf("\n\n");
	// print_ast(ast->root, 0);
	// ft_printf("\n\n");
	tokenlist_clear(ast->tokenlist);
	clear_ast(ast->root);
	free(ast);
}

void	exit_prompt()
{
	printf("\033[u\033[1B\033[1A");
	printf("exit\n");
	exit(-1);
}

int	prompt(void)
{
	char			*line;
	char			*new_line;
	char			*join;
	struct termios	old_term;
	t_ast			*ast;
	int				err;

	err = 0;
	set_echoctl(&old_term);
    while(1)
	{
		set_signal(1);
		printf("Nutshell $ \033[s\b\b\b\b\b\b\b\b\b\b\b");
		line = readline("Nutshell $ ");
        if (!line)
			exit_prompt();
		if (*line != '\0')
		{
			while (1)
			{
				err = 0;
				// ast = parse(line, &err);
				ast = parse(line);
				if (err)
				{
					printf("> \033[s\b\b");
					new_line = readline("> ");
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
			if (err)
				continue ;
			ctrl_cmd(ast);
			if (ast != NULL)
				ast_clear(ast);
			add_history(line);
		}
		free(line);
    }
	restore_echoctl(&old_term);
	return (0);
}
