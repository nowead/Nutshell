/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/06/10 21:07:02 by damin            ###   ########.fr       */
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

	set_echoctl(&old_term);
	set_signal(1);
    while(1)
	{
		printf("Nutshell $ \033[s");
		printf("\b\b\b\b\b\b\b\b\b\b\b");
		line = readline("Nutshell $ ");
		// ft_printf("%s\n\n", line);
        if (!line)
			exit_prompt();
		if (*line != '\0')
		{
			add_history(line);
			ast = parse(line);
			ctrl_cmd(ast);
			if (ast != NULL)
				ast_clear(ast);
		}
		free(line);
    }
	restore_echoctl(&old_term);
	return (0);
}
