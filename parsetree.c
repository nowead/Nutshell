/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:58:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/18 17:47:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_parsetree_node	*new_parsetree_node(int	index, t_symbol sym, t_token *token, size_t child_num)
{
	t_parsetree_node	*node;

	node = (t_parsetree_node *)malloc(sizeof(t_parsetree_node));
	if (node == NULL)
		return (NULL);
	node->child = (t_parsetree_node **)malloc(sizeof(t_parsetree_node *) * child_num);
	if (node->child == NULL)
	{
		free(node);
		return (NULL);
	}
	node->child_num = child_num;
	node->index = index;
	node->sym = sym;
	node->token = token;
	return (node);
}

void	free_parsetree_node(t_parsetree_node *root, t_parsetree_node *node)
{
	if (root != node)
		node->parent->child[node->index] = NULL;
	free(node->child);
	*node = (t_parsetree_node){};
	free(node);
	node = NULL;
}

void	clear_parsetree(t_parsetree_node *root, t_parsetree_node *node)
{
	int	i;

	if (node->child_num == 0)
	{
		free_parsetree_node(root, node);
		return ;
	}
	i = 0;
	while (i < node->child_num)
	{
		clear_parsetree(root, node->child[i]);
		i++;
	}
	free_parsetree_node(root, node);
}
