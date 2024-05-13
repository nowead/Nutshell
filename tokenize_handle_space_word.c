/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle_space_word.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:57:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/13 15:16:38 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

// Handles spaces and separates tokens
void	handle_space(t_token_handler_args *args, size_t i)
{
	if (i > 0 && *(args->tokentype) != TOK_UNKNOWN)
		if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
		ft_substr(args->input, *(args->tok_start), \
		i - *(args->tok_start)))) == -1)
			tokenize_err_exit(args->tokenlist, "token allocation fail");
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
			tokenize_err_exit(args->tokenlist, "token allocation fail");
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
