/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/19 22:54:27 by seonseo          ###   ########.fr       */
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

t_tokentype	current_tokentype(t_tokenlist_node **tokenlist_node)
{
	return ((*tokenlist_node)->token->type);
}

int	accept(t_tokentype tokentype, t_tokenlist_node **tokenlist_node)
{
    if (current_tokentype(tokenlist_node) == tokentype)
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
