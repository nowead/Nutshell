/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_addition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:36:30 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 21:37:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_toknode(t_tokenlist *tokenlist, \
t_toknode *toknode)
{
	if (tokenlist->head == NULL)
	{
		tokenlist->head = toknode;
		tokenlist->back = toknode;
	}
	else
	{
		tokenlist->back->next = toknode;
		toknode->prev = tokenlist->back;
		tokenlist->back = toknode;
	}
	(tokenlist->size)++;
}

int	tokenlist_add(t_tokenlist *tokenlist, t_token *token)
{
	t_toknode	*toknode;

	if (token == NULL)
		return (-1);
	toknode = new_toknode(token);
	if (toknode == NULL)
	{
		free_token(token);
		return (-1);
	}
	add_toknode(tokenlist, toknode);
	return (0);
}
