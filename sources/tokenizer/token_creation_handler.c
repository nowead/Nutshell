/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:57:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 22:02:36 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles creation of a single token
// Takes token handler arguments and the current index as input
// Determines the type of token based on the current character
// Calls appropriate handler functions for different token types
int	handle_token_creation(t_token_handler_args *args, size_t *i)
{
	if (is_operator((args->input)[*i]) && *(args->quotetype) == NO_QUOTE)
	{
		if (handle_operator(args, *i) == -1)
			return (-1);
	}
	else if ((args->input)[*i] == '&' && \
	is_part_of_operator(args->input, *i, (*i) + 1) && \
	*(args->quotetype) == NO_QUOTE)
	{
		if (handle_and_if_operator(args, i) == -1)
			return (-1);
	}
	else if (ft_isspace((args->input)[*i]) && *(args->quotetype) == NO_QUOTE)
	{
		if (handle_space(args, *i) == -1)
			return (-1);
	}
	else if (handle_word(args, *i) == -1)
		return (-1);
	(*i)++;
	return (0);
}

// Handles spaces and separates tokens
// Takes token handler arguments and the current index as input
// Adds the current token to the token list if the token type is 'TOK_WORD'
// Resets the token type to 'TOK_UNKNOWN'
int	handle_space(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) == TOK_WORD)
	{
		if (tokenlist_add(args->tokenlist, \
		new_word_token(ft_substr(args->input, \
		*(args->tok_start), i - *(args->tok_start)))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	else if (*(args->tokentype) >= TOK_LPAREN)
	{
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	*(args->tokentype) = TOK_UNKNOWN;
	return (0);
}

// Handles word tokens
// Takes token handler arguments and the current index as input
// Checks if the current token type is an operator and adds it to the token list
// Toggles quote states for single and double quotes
// Sets the token type to 'TOK_WORD'
int	handle_word(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) >= TOK_LPAREN)
	{
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
		*(args->tok_start) = i;
	}
	else if (*(args->tokentype) == TOK_UNKNOWN)
		*(args->tok_start) = i;
	*(args->tokentype) = TOK_WORD;
	handle_quote(args, i);
	return (0);
}

void	handle_quote(t_token_handler_args *args, size_t i)
{
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
