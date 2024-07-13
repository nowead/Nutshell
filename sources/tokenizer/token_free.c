/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:37:21 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 21:05:14 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	free(token->str);
	token->str = NULL;
	if (token->is_quoted)
	{
		free(token->is_quoted);
		token->is_quoted = NULL;
	}
	free(token);
	token = NULL;
}

void	free_toknode(t_toknode *toknode)
{
	free_token(toknode->token);
	free(toknode);
}

void	*clear_tokenlist(t_tokenlist *tokenlist)
{
	t_toknode	*curr;
	t_toknode	*prev;

	if (tokenlist == NULL)
		return (NULL);
	prev = NULL;
	curr = tokenlist->head;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		free_toknode(prev);
	}
	prev = NULL;
	free(tokenlist);
	tokenlist = NULL;
	return (NULL);
}
