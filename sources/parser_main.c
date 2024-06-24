/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/24 13:59:22 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak_check(void)
{
	system("leaks minishell");
}

int main()
{
	prompt();
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
