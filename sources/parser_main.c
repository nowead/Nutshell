/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/05 14:34:28 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leak_check(void)
{
	system("leaks parser");
}

int main()
{
	t_ast	*ast;

	// atexit(leak_check);
	ast = parse("a=b c=d aaa g=h");
	if (ast != NULL)
	{
		// print_tokenlist(ast->tokenlist);
		ft_printf("\n\n");
		print_ast(ast->root, 0);
		ft_printf("\n\n");
		tokenlist_clear(ast->tokenlist);
		clear_ast(ast->root);
		free(ast);
	}
    return (0);
}
