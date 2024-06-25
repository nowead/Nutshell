/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/25 19:38:38 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak_check(void)
{
	system("leaks minishell");
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	prompt(envp);
	// t_ast	*ast;
	// int		incomplete_cmd;

	// atexit(leak_check);
	// ast = parse("< infile cmd > outfile | cmd2", &incomplete_cmd);
	// if (ast != NULL && incomplete_cmd == 0)
	// {
	// 	print_ast(ast->root, 0);
	// 	clear_ast(ast);
	// }
	// else
	// 	printf("error!\n");
	return (0);
}
