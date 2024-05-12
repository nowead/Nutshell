/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handle_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:57:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/12 22:34:08 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// Handles operator tokens
void	handle_operator(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) != TOK_OPERATOR)
	{
		// Finish the current token if it's not an operator
		if (*(args->tokentype) != TOK_UNKNOWN)
			if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
			ft_substr(args->input, *(args->tok_start), \
			i - *(args->tok_start)))) == -1)
				tokenizer_err_exit(args->tokenlist, "token allocation fail");
		*(args->tokentype) = TOK_OPERATOR;
		*(args->tok_start) = i;
	}
	else if (!is_part_of_operator(args->input, *(args->tok_start), i))
	{
		// Start a new operator token if it's not a continuation of the current operator
		if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
		ft_substr(args->input, *(args->tok_start), \
		i - *(args->tok_start)))) == -1)
			tokenizer_err_exit(args->tokenlist, "token allocation fail");
		*(args->tok_start) = i;
	}
}

void	handle_and_if_operator(t_token_handler_args *args, size_t *i)
{
	if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
			ft_substr(args->input, *(args->tok_start), \
			i - *(args->tok_start)))) == -1)
				tokenizer_err_exit(args->tokenlist, "token allocation fail");
}
//dsfds&&
//.    

// Handles spaces and separates tokens
void	handle_space(t_token_handler_args *args, size_t i)
{
	if (i > 0 && *(args->tokentype) != TOK_UNKNOWN)
		if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
		ft_substr(args->input, *(args->tok_start), \
		i - *(args->tok_start)))) == -1)
			tokenizer_err_exit(args->tokenlist, "token allocation fail");
	*(args->tokentype) = TOK_UNKNOWN; // Reset token type after handling space
}

// Handles word tokens
void	handle_word(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) == TOK_OPERATOR)
	{
		// If currently an operator, finish it and start a new token
		if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
		ft_substr(args->input, *(args->tok_start), \
		i - *(args->tok_start)))) == -1)
			tokenizer_err_exit(args->tokenlist, "token allocation fail");
		*(args->tok_start) = i;
	}
	else if (*(args->tokentype) == TOK_UNKNOWN)
		*(args->tok_start) = i; // Start a new token if none is currently active
	*(args->tokentype) = TOK_WORD; // Mark current token as a word
	// Handle single and double quotes by toggling quote state
	if ((args->input)[i] == '\'' && *(args->quotetype) != DOUBLE_QUOTE)
	{
		if (*(args->quotetype) == NO_QUOTE)
			*(args->quotetype) = SINGLE_QUOTE;
		else
			*(args->quotetype) = NO_QUOTE;
	}
	else if ((args->input)[i] == '\"' && *(args->quotetype) != SINGLE_QUOTE)
	{
		if (*(args->quotetype) == NO_QUOTE)
			*(args->quotetype) = DOUBLE_QUOTE;
		else
			*(args->quotetype) = NO_QUOTE;
	}
}

// Checks if a character is an operator
int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

// Checks if a sequence forms an operator
int	is_part_of_operator(const char *input, size_t tok_start, size_t i)
{
	int	len; // Length of the substring being considered

	len = i - tok_start + 1; // Calculate length of current operator substring
	if (len == 2)
	{
		// Check for specific compound operators '<<' or '>>'
		if (ft_strncmp("&&", &input[tok_start], len) == 0 || \
			ft_strncmp("||", &input[tok_start], len) == 0 || \
			ft_strncmp("<<", &input[tok_start], len) == 0 || \
			ft_strncmp(">>", &input[tok_start], len) == 0)
			return (1); // Return 1 if the substring is a recognized compound operator
		else
			return (0); // Return 0 if the substring is not a recognized compound operator
	}
	return (0); // Return 0 if the substring length is not 2, hence not a compound operator
}
