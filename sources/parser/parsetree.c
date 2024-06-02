/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:58:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/01 20:32:27 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new_ast_node(int sibling_index, t_symbol sym, t_token *token, size_t child_num)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->child_num = child_num;
	node->sibling_index = sibling_index;
	node->sym = sym;
	node->token = token;
	return (node);
}

int	add_ast_child(t_ast_node *node, t_ast_node *child, t_ast_err *err)
{
	if (child == NULL)
	{
		err->errnum = ENOMEM;
		return (-1);
	}
	if (node->child == NULL)
	{
		node->child = \
		(t_ast_node **)ft_calloc(node->child_num, sizeof(t_ast_node *));
		if (node->child == NULL)
		{
			err->errnum = ENOMEM;
			return (-1);
		}
	}
	node->child[child->sibling_index] = child;
	child->parent = node;
	return (0);
}

void	free_ast_node(t_ast_node *node)
{
	if (node->parent != NULL)
		node->parent->child[node->sibling_index] = NULL;
	free(node->child);
	*node = (t_ast_node){};
	free(node);
	node = NULL;
}

void	clear_ast(t_ast_node *node)
{
	int	i;

	if (node == NULL)
		return ;
	if (node->child == NULL)
	{
		free_ast_node(node);
		return ;
	}
	i = 0;
	while (i < node->child_num)
	{
		clear_ast(node->child[i]);
		i++;
	}
	free_ast_node(node);
}
