/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:53:49 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/03 21:41:16 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Main function to tokenize a given input string.
// It returns a pointer to a t_tokenlist structure containing the tokens or NULL if an error occurs.
t_tokenlist	*tokenize(const char *input)
{
	t_tokenlist	*tokenlist;

	if (input == NULL)
		return (NULL);
	// Attempt to create a new token list to store tokens.
	tokenlist = new_tokenlist();
	if (tokenlist == NULL)
		tokenize_err_exit(NULL, "tokenlist allocation fail");
	// Process the tokens by examining each character in the input string.
	process_tokens(input, tokenlist);
	// Return the populated token list.
	return (tokenlist);
}

// Processes input to generate tokens
void	process_tokens(const char *input, t_tokenlist *tokenlist)
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
		handle_token_creation(&args, &i); // Handle creation of token based on current character
		i++;
	}
	// After processing all characters, handle any unclosed quotes or final tokens
	if (quotetype != NO_QUOTE)
	{
		errno = EINVAL;
		tokenize_err_exit(tokenlist, "unclosed quotation detected"); // Error if quote is not closed
	}
	else
		add_final_token(&args, i);
}

void	add_final_token(t_token_handler_args *args, size_t i)
{
	// Check if the current token type is a word
	if (*(args->tokentype) == WORD)
	{
		// Create a new word token and add it to the token list
		if (tokenlist_add(args->tokenlist, new_word_token(\
		ft_substr(args->input, *(args->tok_start), i - *(args->tok_start)))) == -1)
			tokenize_err_exit(args->tokenlist, "token allocation fail");
	}
	// Check if the current token type is an operator
	else if (*(args->tokentype) >= LPAREN)
	{
		// Create a new operator token and add it to the token list
		if (tokenlist_add(args->tokenlist, new_operator_token(*(args->tokentype))) == -1)
			tokenize_err_exit(args->tokenlist, "token allocation fail");
	}
	if (tokenlist_add(args->tokenlist, new_operator_token(NEWLINE)) == -1)
		tokenize_err_exit(args->tokenlist, "token allocation fail");
}

// Handles errors by cleaning up and exiting
void	tokenize_err_exit(t_tokenlist *tokenlist, char *err_msg)
{
	if (tokenlist != NULL)
		tokenlist_clear(tokenlist); // Free all allocated tokens and the token list itself
	perror(err_msg); // Print the error message to standard error
	exit(EXIT_FAILURE); // Exit the program with a failure status
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
		if (ft_printf("%s", tokentype_str) == -1)
			return (-1);
		if (ft_printf(":%s\n", curr->token->str) == -1)
			return (-1);
		curr = curr->next;
	}
	return (0);
}
