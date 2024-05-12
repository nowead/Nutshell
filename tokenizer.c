/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:53:49 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/12 22:35:18 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// Main function to tokenize a given input string.
// It returns a pointer to a t_tokenlist structure containing the tokens or NULL if an error occurs.
t_tokenlist	*tokenizer(const char *input)
{
	t_tokenlist	*tokenlist;

	if (input == NULL)
		return (NULL);
	// Attempt to create a new token list to store tokens.
	tokenlist = new_tokenlist();
	if (tokenlist == NULL)
		tokenizer_err_exit(NULL, "tokenlist allocation fail");
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
	tokentype = TOK_UNKNOWN;  // Start with unknown token type
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
		tokenizer_err_exit(tokenlist, "unclosed quotation detected"); // Error if quote is not closed
	else if (tokentype != TOK_UNKNOWN)
	// Close a token if there is an unclosed token
		if (tokenlist_add(tokenlist, new_token(tokentype, \
		ft_substr(input, tok_start, i - tok_start))) == -1)
			tokenizer_err_exit(tokenlist, "token allocation fail");
}

// Handles creation of a single token
void	handle_token_creation(t_token_handler_args *args, size_t *i)
{
	if (is_operator((args->input)[*i]) && *(args->quotetype) == NO_QUOTE)
		handle_operator(args, *i); // Handle operators outside of quotes
	else if ((args->input)[*i] == '&' && is_part_of_operator(args->input, *i, (*i) + 1))
		handle_and_if_operator(args, i);
	else if (ft_isspace((args->input)[*i]) && *(args->quotetype) == NO_QUOTE)
		handle_space(args, *i); // Handle spaces outside of quotes
	else
		handle_word(args, *i); // Handle words or quoted text
}

// Handles errors by cleaning up and exiting
void	tokenizer_err_exit(t_tokenlist *tokenlist, char *err_msg)
{
	if (tokenlist != NULL)
		tokenlist_clear(tokenlist); // Free all allocated tokens and the token list itself
	perror(err_msg); // Print the error message to standard error
	exit(EXIT_FAILURE); // Exit the program with a failure status
}

// Prints all tokens in the list for debugging
int	print_tokenlist(t_tokenlist *tokenlist)
{
	t_token	*curr;

	curr = tokenlist->head;
	while (curr)
	{
		if (ft_printf("%d:%s\n", curr->type, curr->str) == -1)
			return (-1);
		curr = curr->next;
	}
	return (0);
}

int	main(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = tokenizer(" asd|sdf\"d<<<'s' f\" >><< f ");
	print_tokenlist(tokenlist);
	ft_printf("size:%d\n", tokenlist->size);
	tokenlist_clear(tokenlist);
}
