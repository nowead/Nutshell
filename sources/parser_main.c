/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/18 20:16:35 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	leak_check(void)
// {
// 	system("leaks parser");
// }

int main()
{
	t_ast	*ast;
	int		incomplete_cmd;

	incomplete_cmd = 0;
	ast = parse("ls && |", &incomplete_cmd);
	if (ast != NULL)
	{
		print_tokenlist(ast->tokenlist);
		tokenlist_clear(ast->tokenlist);
		clear_ast(ast->root);
		free(ast);
	}
	else if (incomplete_cmd == 1)
	{
		printf("> \n");
	}
    return (0);
	// t_tokenlist	*tokenlist;

	// atexit(leak_check);
	// tokenlist = tokenize("a b c");
	// expand_parameter(tokenlist);
	// print_tokenlist(tokenlist);
	// tokenlist_clear(tokenlist);
	// return (0);
}
