/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:58:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/23 19:27:50 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new_ast_node(int sibling_index, t_symbol sym, t_token *token)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->sibling_index = sibling_index;
	node->sym = sym;
	node->token = token;
	return (node);
}

int	add_ast_child(t_ast_node *node, t_ast_node *child, t_ast_err *err, size_t max_child_num)
{
	if (child == NULL)
	{
		err->errnum = ENOMEM;
		return (-1);
	}
	if (node->child == NULL)
	{
		node->child = \
		(t_ast_node **)ft_calloc(max_child_num, sizeof(t_ast_node *));
		if (node->child == NULL)
		{
			err->errnum = ENOMEM;
			return (-1);
		}
	}
	node->child[child->sibling_index] = child;
	(node->child_num)++;
	child->parent = node;
	return (0);
}

void	free_ast_node(t_ast_node *node)
{
	if (node->parent)
	{
		node->parent->child[node->sibling_index] = NULL;
		(node->parent->child_num)--;
		if (node->parent->child_num == 0)
		{
			free(node->parent->child);
			node->parent->child = NULL;
		}
	}
	*node = (t_ast_node){};
	free(node);
	node = NULL;
}

void	clear_ast_tree(t_ast_node *node)
{
	size_t	i;

	if (node->child == NULL)
	{
		free_ast_node(node);
		return ;
	}
	i = 0;
	while (node->child_num)
	{
		clear_ast_tree(node->child[i]);
		i++;
	}
	free_ast_node(node);
}

void	clear_ast(t_ast	*ast)
{
	clear_tokenlist(ast->tokenlist);
	clear_ast_tree(ast->root);
	free(ast);
}
