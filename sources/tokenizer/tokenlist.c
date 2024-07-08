/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:59:38 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 21:13:39 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist	*new_tokenlist(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = (t_tokenlist *)ft_calloc(1, sizeof(t_tokenlist));
	return (tokenlist);
}

t_token	*new_word_token(char *str)
{
	t_token	*new_token;

	if (str == NULL)
		return (NULL);
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
	{
		free(str);
		return (NULL);
	}
	new_token->type = TOK_WORD;
	new_token->str = str;
	return (new_token);
}

t_token	*new_operator_token(t_tokentype type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = type;
	return (new_token);
}

t_toknode	*new_toknode(t_token *token)
{
	t_toknode	*toknode;

	toknode = (t_toknode *)ft_calloc(1, sizeof(t_toknode));
	if (toknode == NULL)
		return (NULL);
	toknode->token = token;
	return (toknode);
}

void	tokenlist_add_node(t_tokenlist *tokenlist, \
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
	tokenlist_add_node(tokenlist, toknode);
	return (0);
}

void	free_token(t_token *token)
{
	free(token->str);
	token->str = NULL;
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
