/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:57:38 by damin             #+#    #+#             */
/*   Updated: 2024/06/18 20:26:29 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_READLINE
#include "minishell.h"

void	exec_cmd(t_ast_node *node)
{
	if (node == NULL) 
		return ;
	e_and_or(node);
}

void	ctrl_cmd(t_ast *ast)
{
	ft_printf("\n\n");
	if (ast != NULL)
		print_ast(ast->root, 0);
	ft_printf("\n\n\n");
	// print_tokenlist(ast->tokenlist);
	// ft_printf("\n\n");
	if (ast != NULL)
		exec_cmd(ast->root);
}
