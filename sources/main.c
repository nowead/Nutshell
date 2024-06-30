/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/30 19:48:31 by seonseo          ###   ########.fr       */
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
	run_shell(envp);
	// t_ast	*ast;
	// int		incomplete_cmd;

	// atexit(leak_check);
	// ast = parse("$a", &incomplete_cmd, envp);
	// if (ast != NULL && incomplete_cmd == 0)
	// {
	// 	print_ast(ast->root, 0);
	// 	clear_ast(ast);
	// }
	// else
	// 	printf("error!\n");
	return (0);
}
