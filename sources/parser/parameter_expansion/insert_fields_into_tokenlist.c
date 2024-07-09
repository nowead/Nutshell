/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_fields_into_tokenlist.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:22:31 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:22:44 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_fields_into_tokenlist(t_tokenlist *tokenlist, \
t_toknode *toknode, t_tokenlist *fields)
{
	t_toknode	*prev;
	t_toknode	*next;

	prev = toknode->prev;
	next = toknode->next;
	if (prev != NULL)
	{
		prev->next = fields->head;
		fields->head->prev = prev;
	}
	else
		tokenlist->head = fields->head;
	if (next != NULL)
	{
		next->prev = fields->back;
		fields->back->next = next;
	}
	else
		tokenlist->back = fields->back;
}
