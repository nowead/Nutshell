/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:59:38 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 21:47:27 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_toknode(t_tokenlist *tokenlist, t_toknode *toknode)
{
	t_toknode	*prev;
	t_toknode	*next;

	prev = toknode->prev;
	next = toknode->next;
	toknode->prev = NULL;
	toknode->next = NULL;
	if (prev)
		prev->next = next;
	else
		tokenlist->head = next;
	if (next)
		next->prev = prev;
	else
		tokenlist->back = prev;
	(tokenlist->size)--;
}

void	delete_toknode(t_tokenlist *tokenlist, t_toknode *toknode)
{
	pop_toknode(tokenlist, toknode);
	free_toknode(toknode);
}
