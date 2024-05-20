/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/20 23:18:25 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_ast_node *parse(const char* input)
{
	t_tokenlist			*tokenlist;
	t_tokenlist_node	*tokenlist_node;
	t_ast_node			*root;

	tokenlist = tokenize(input);
	tokenlist_node = tokenlist->head;
	root = program(&tokenlist_node);
	return (root);
}

void	set_next_token(t_tokenlist_node **tokenlist_node)
{
	(*tokenlist_node) = (*tokenlist_node)->next;
}

t_tokentype	curr_tokentype(t_tokenlist_node **tokenlist_node)
{
	return ((*tokenlist_node)->token->type);
}

t_token	*curr_token(t_tokenlist_node **tokenlist_node)
{
	return ((*tokenlist_node)->token);
}

int	accept(t_tokentype tokentype, t_tokenlist_node **tokenlist_node)
{
    if (curr_tokentype(tokenlist_node) == tokentype)
	{
        set_next_token(tokenlist_node);
        return (1);
    }
    return (0);
}

int	expect(t_tokentype tokentype, t_tokenlist_node **tokenlist_node)
{
    if (accept(tokentype, tokenlist_node))
        return (1);
    ft_dprintf(2, "expect: unexpected symbol");
    return (0);
}

t_ast_node	*program(t_tokenlist_node **tokenlist_node)
{
	t_ast_node	*root;

	root = new_ast_node(0, AND_OR, NULL, 2);
	if (root == NULL)
		return (NULL);
	if (and_or(tokenlist_node, root))
		return (root);
	clear_ast(root);
	return (NULL);
}

int	and_or(t_tokenlist_node **tokenlist_node, t_ast_node *curr)
{
	add_ast_node_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL, 2));
	add_ast_node_child(curr, new_ast_node(1, AND_OR_, NULL, 3));
	if (pipe_sequence(tokenlist_node, curr->child[0]))
	{
		if (and_or_(tokenlist_node, curr->child[1]))
			return (1);
	}
	return (0);
}

int	and_or_(t_tokenlist_node **tokenlist_node, t_ast_node *curr)
{
	if (curr_tokentype(tokenlist_node) == AND_IF || \
	curr_tokentype(tokenlist_node) == OR_IF)
		add_ast_node_child(curr, new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 2));
		add_ast_node_child(curr, new_ast_node(1, PIPE_SEQUENCE, NULL, 3));
		add_ast_node_child(curr, new_ast_node(2, AND_OR_, NULL, 3));
	if (accept(AND_IF, tokenlist_node))
	{
		if (pipe_sequence(tokenlist_node, curr->child[1]))
			return (and_or_(tokenlist_node, curr->child[2]));
		return (0);
	}
	else if (accept(OR_IF, tokenlist_node))
	{
		if (pipe_sequence(tokenlist_node, curr->child[1]))
			return (and_or_(tokenlist_node, curr->child[2]));
		return (0);
	}
	else if (*tokenlist_node == NULL)
		return (1);
	return (0);
}
