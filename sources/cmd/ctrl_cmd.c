/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:57:38 by damin             #+#    #+#             */
/*   Updated: 2024/06/12 20:37:03 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_READLINE
#include "minishell.h"

void	exec(t_ast_node *node)
{
	// printf("Symbol: %s\n", get_symbol_type_string(node->sym));
	// printf("  Token Type: %s\n", get_token_type_string(node->token->type));
	// printf("  Token String: %s\n", node->token->str);
	// if (node->sym == IO_HERE)
	// 	e_io_here(node->parent->child[i + 1]->token->str);
	// 	//node->token->str
}

// void	exec_cmd(t_ast_node *node)
// {
// 	size_t	i;

// 	if (node == NULL) 
// 		return ;
// 	//printf("Symbol: %s\n", get_symbol_type_string(node->sym));
// 	// printf("Sibling num: %d\n", node->sibling_index);
// 	if (node->token)
// 		exec(node);
// 	i = 0;
// 	while (node->child && i < node->child_num)
// 	{
// 		exec_cmd(node->child[i]);
// 		i++;
// 	}
// }

void	exec_cmd(t_ast_node *node)
{
	if (node == NULL) 
		return ;
	//printf("Symbol: %s\n", get_symbol_type_string(node->sym));
	// printf("Sibling num: %d\n", node->sibling_index);
	e_and_or(node);
}

void	ctrl_cmd(t_ast *ast)
{
	// ft_printf("\n\n");
	// print_ast(ast->root, 0);
	// ft_printf("\n\n\n");
	// print_tokenlist(ast->tokenlist);
	// ft_printf("\n\n");
	exec_cmd(ast->root);
}
