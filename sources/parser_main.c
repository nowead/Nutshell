/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/23 17:29:24 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	void	leak_check(void)
	{
		system("leaks minishell");
	}

int main()
{
	t_ast		*ast;
	int			incomplete_cmd;

	atexit(leak_check);
	ast = parse("a", &incomplete_cmd);
	print_ast(ast->root, 0);
	clear_ast(ast);
	return (0);
}
