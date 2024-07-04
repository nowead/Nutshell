/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:59:38 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/04 22:30:57 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a new token list
t_tokenlist	*new_tokenlist(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = (t_tokenlist *)ft_calloc(1, sizeof(t_tokenlist)); // Allocate memory for a new token list
	return (tokenlist);
}

// Creates a new token
t_token	*new_word_token(char *str)
{
	t_token	*new_token;

	if (str == NULL)
		return (NULL);
	new_token = (t_token *)ft_calloc(1, sizeof(t_token)); // Allocate memory for a new token
	if (new_token == NULL)
	{
		free(str);
		return (NULL); // Return NULL if memory allocation fails
	}
	new_token->type = WORD;
	new_token->str = str;
	return (new_token);
}

t_token *new_operator_token(t_tokentype type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token)); // Allocate memory for a new token
	if (new_token == NULL)
		return (NULL); // Return NULL if memory allocation fails
	new_token->type = type;
	return (new_token);
}

t_tokenlist_node	*new_tokenlist_node(t_token *token)
{
	t_tokenlist_node	*tokenlist_node;

	tokenlist_node = (t_tokenlist_node *)ft_calloc(1, sizeof(t_tokenlist_node));
	if (tokenlist_node == NULL)
		return (NULL);
	tokenlist_node->token = token;
	return (tokenlist_node);
}

void	tokenlist_add_node(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node)
{
	if (tokenlist->head == NULL)  // If list is empty, initialize head and back
	{
		tokenlist->head = tokenlist_node;
		tokenlist->back = tokenlist_node;
	}
	else // Otherwise, append to the end of the list
	{
		tokenlist->back->next = tokenlist_node;
		tokenlist_node->prev = tokenlist->back;
		tokenlist->back = tokenlist_node;
	}
	(tokenlist->size)++; // Increment the size of the token list
}

// Adds a token to the list
int	tokenlist_add(t_tokenlist *tokenlist, t_token *token)
{
	t_tokenlist_node	*tokenlist_node;

	if (token == NULL)
		return (-1);
	tokenlist_node = new_tokenlist_node(token);
	if (tokenlist_node == NULL)
	{
		free_token(token);
		return (-1);
	}
	tokenlist_add_node(tokenlist, tokenlist_node);
	return (0);
}

void	free_token(t_token *token)
{
	free(token->str);
	token->str = NULL;
	free(token);
	token = NULL;
}

void	free_tokenlist_node(t_tokenlist_node *tokenlist_node)
{
	free_token(tokenlist_node->token);
	free(tokenlist_node);
}

// Clears the token list, freeing all resources
void	*clear_tokenlist(t_tokenlist *tokenlist)
{
	t_tokenlist_node	*curr;
	t_tokenlist_node	*prev;

	if (tokenlist == NULL)
		return (NULL); // If the token list is NULL, there's nothing to clear, so return immediately
	prev = NULL;
	curr = tokenlist->head; // Start with the first token in the list
	while (curr)
	{
		prev = curr; // Hold the current token
		curr = curr->next; // Move to the next token
		free_tokenlist_node(prev); // Free the tokenlist_node structure itself
	}
	prev = NULL; // Nullify the temporary token pointer
	free(tokenlist); // Free the token list structure
	tokenlist = NULL; // Nullify the token list pointer
	return (NULL);
}

void	pop_tokenlist_node(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node)
{
	t_tokenlist_node	*prev;
	t_tokenlist_node	*next;

	prev = tokenlist_node->prev;
	next = tokenlist_node->next;
	tokenlist_node->prev = NULL;
	tokenlist_node->next = NULL;
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

void	delete_tokenlist_node(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node)
{
	pop_tokenlist_node(tokenlist, tokenlist_node);
	free_tokenlist_node(tokenlist_node);
}
