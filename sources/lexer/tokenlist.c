/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:59:38 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/23 19:47:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates a new token list
t_tokenlist	*new_tokenlist(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = (t_tokenlist *)malloc(sizeof(t_tokenlist)); // Allocate memory for a new token list
	if (tokenlist == NULL)
		return (NULL); // Return NULL if memory allocation fails
	*tokenlist = (t_tokenlist){}; // Initialize the token list to empty
	return (tokenlist);
}

// Creates a new token
t_token	*new_word_token(char *str)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token)); // Allocate memory for a new token
	if (new_token == NULL)
		return (NULL); // Return NULL if memory allocation fails
	new_token->type = WORD;
	new_token->str = str;
	return (new_token);
}

t_token *new_operator_token(t_tokentype type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token)); // Allocate memory for a new token
	if (new_token == NULL)
		return (NULL); // Return NULL if memory allocation fails
	new_token->type = type;
	new_token->str = NULL;
	return (new_token);
}

t_tokenlist_node	*new_tokenlist_node(t_token *token)
{
	t_tokenlist_node	*tokenlist_node;

	tokenlist_node = (t_tokenlist_node *)malloc(sizeof(t_tokenlist_node));
	if (tokenlist_node == NULL)
		return (NULL);
	*tokenlist_node = (t_tokenlist_node){};
	tokenlist_node->token = token;
	return (tokenlist_node);
}

// Adds a token to the list
int	tokenlist_add(t_tokenlist *tokenlist, t_token *token)
{
	t_tokenlist_node	*tokenlist_node;

	if (token == NULL)
		return (-1);  // Return error if token is NULL
	tokenlist_node = new_tokenlist_node(token);
	if (tokenlist_node == NULL)
	{
		free_token(token);
		return (-1);
	}
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
	return (0);
}

void	free_token(t_token *token)
{
	free(token->str);
	token->str = NULL;
	free(token);
	token = NULL;
}

// Clears the token list, freeing all resources
void	tokenlist_clear(t_tokenlist *tokenlist)
{
	t_tokenlist_node	*curr;
	t_tokenlist_node	*prev;

	if (tokenlist == NULL)
		return ; // If the token list is NULL, there's nothing to clear, so return immediately
	prev = NULL;
	curr = tokenlist->head; // Start with the first token in the list
	while (curr)
	{
		prev = curr; // Hold the current token
		curr = curr->next; // Move to the next token
		free_token(prev->token);
		free(prev); // Free the tokenlist_node structure itself
	}
	prev = NULL; // Nullify the temporary token pointer
	free(tokenlist); // Free the token list structure
	tokenlist = NULL; // Nullify the token list pointer
}
