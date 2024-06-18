/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/06/18 20:11:00 by seonseo          ###   ########.fr       */
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
	struct termios	old_term;
	t_ast			*ast;
	int				incomplete_cmd;

	set_echoctl(&old_term);
    while(1)
	{
		set_signal(1);
		printf("Nutshell $ \033[s");
		printf("\b\b\b\b\b\b\b\b\b\b\b");
		line = readline("Nutshell $ ");
        if (!line)
			exit_prompt();
		if (*line != '\0')
		{
			ast = parse(line, &incomplete_cmd);
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
