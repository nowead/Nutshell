/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:59:38 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/12 14:19:33 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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
t_token	*new_token(t_tokentype type, char *str)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token)); // Allocate memory for a new token
	if (new_token == NULL)
		return (NULL); // Return NULL if memory allocation fails
	*new_token = (t_token){}; // Initialize the token to empty
	new_token->type = type;
	new_token->str = str;
	return (new_token);
}

// Adds a token to the list
int	tokenlist_add(t_tokenlist *tokenlist, t_token *token)
{
	if (token == NULL)
		return (-1);  // Return error if token is NULL
	if (tokenlist->head == NULL)  // If list is empty, initialize head and back
	{
		tokenlist->head = token;
		tokenlist->back = token;
	}
	else // Otherwise, append to the end of the list
	{
		tokenlist->back->next = token;
		token->prev = tokenlist->back;
		tokenlist->back = token;
	}
	(tokenlist->size)++; // Increment the size of the token list
	return (0);
}

// Clears the token list, freeing all resources
void	tokenlist_clear(t_tokenlist *tokenlist)
{
	t_token	*curr;
	t_token	*prev;

	if (tokenlist == NULL)
		return ; // If the token list is NULL, there's nothing to clear, so return immediately
	prev = NULL;
	curr = tokenlist->head; // Start with the first token in the list
	while (curr)
	{
		prev = curr; // Hold the current token
		curr = curr->next; // Move to the next token
		free(prev->str); // Free the string associated with the current token
		prev->str = NULL; // Nullify the string pointer after freeing
		free(prev); // Free the token structure itself
	}
	prev = NULL; // Nullify the temporary token pointer
	free(tokenlist); // Free the token list structure
	tokenlist = NULL; // Nullify the token list pointer
}
