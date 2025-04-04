/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:53:49 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/23 22:55:33 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Main function to tokenize a given input string.
// It returns a pointer to a t_tokenlist structure containing the tokens or NULL if an error occurs.
t_tokenlist	*tokenize(const char *input, int *incomplete_cmd)
{
	t_tokenlist	*tokenlist;

	if (input == NULL)
		return (NULL);
	// Attempt to create a new token list to store tokens.
	tokenlist = new_tokenlist();
	if (tokenlist == NULL)
	{
		perror("tokenlist allocation fail");
		return (NULL);
	}
	// Process the tokens by examining each character in the input string.
	if (process_tokens(input, tokenlist, incomplete_cmd) == -1)
	{
		clear_tokenlist(tokenlist);
		return (NULL);
	}
	// Return the populated token list.
	return (tokenlist);
}

// Processes input to generate tokens
int	process_tokens(const char *input, t_tokenlist *tokenlist, int *incomplete_cmd)
{
	t_tokentype				tokentype;
	t_quotetype				quotetype;
	size_t					tok_start;
	size_t					i;
	t_token_handler_args	args;

	quotetype = NO_QUOTE;  // Start with no active quotes
	tokentype = UNKNOWN;  // Start with unknown token type
	args = (t_token_handler_args){input, &tok_start, \
			&tokentype, &quotetype, tokenlist};
	i = 0;  // Process each character until end of string
	while (input[i])
	{
		if (handle_token_creation(&args, &i) == -1)
			return (-1);
	}
	// After processing all characters, handle any unclosed quotes or final tokens
	if (quotetype != NO_QUOTE)
	{
		*incomplete_cmd = 1; // Error if quote is not closed
		return (-1);
	}
	else if (add_final_token(&args, i) == -1)
		return (-1);
	return (0);
}

int	add_final_token(t_token_handler_args *args, size_t i)
{
	// Check if the current token type is a word
	if (*(args->tokentype) == WORD)
	{
		// Create a new word token and add it to the token list
		if (tokenlist_add(args->tokenlist, new_word_token(\
		ft_substr(args->input, *(args->tok_start), i - *(args->tok_start)))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	// Check if the current token type is an operator
	else if (*(args->tokentype) >= LPAREN)
	{
		// Create a new operator token and add it to the token list
		if (tokenlist_add(args->tokenlist, new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	if (tokenlist_add(args->tokenlist, new_operator_token(NEWLINE)) == -1)
	{
		perror("token allocation fail");
		return (-1);
	}
	return (0);
}

// Prints all tokens in the list for debugging
int	print_tokenlist(t_tokenlist *tokenlist)
{
	t_tokenlist_node	*curr;
	const char			*tokentype_str;

	curr = tokenlist->head;
	while (curr)
	{
		tokentype_str = get_token_type_string(curr->token->type);
		if (ft_printf("%s:", tokentype_str) == -1)
			return (-1);
		ft_printf("quote:%d:", curr->token->quote);
		if (ft_printf("%s\n", curr->token->str) == -1)
			return (-1);
		curr = curr->next;
	}
	return (0);
}
