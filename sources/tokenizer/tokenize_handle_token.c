/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:57:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/04 18:10:43 by seonseo          ###   ########.fr       */
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
		if (handle_operator(args, *i) == -1) // Handle operators outside of quotes
			return (-1);
	}
	else if ((args->input)[*i] == '&' && \
	is_part_of_operator(args->input, *i, (*i) + 1) && \
	*(args->quotetype) == NO_QUOTE)
	{
		if (handle_and_if_operator(args, i) == -1) // Handle '&&' operator outside of quotes
			return (-1);
	}
	else if (ft_isspace((args->input)[*i]) && *(args->quotetype) == NO_QUOTE)
	{
		if (handle_space(args, *i) == -1) // Handle spaces outside of quotes
			return (-1);
	}
	else if (handle_word(args, *i) == -1) // Handle words or quoted text
		return (-1);
	(*i)++;
	return (0);
}

// Handles operator tokens
// Takes token handler arguments and the current index as input
// Classifies and sets the token type to the appropriate single operator
// Adds the token to the token list if necessary
int	handle_operator(t_token_handler_args *args, size_t i)
{
	// Checks if the current token type is not operator
	if (*(args->tokentype) < LPAREN)
	{
		// add new word token to the list If the current token type is a word
		if (*(args->tokentype) == WORD)
			if (tokenlist_add(args->tokenlist, \
			new_word_token(ft_substr(args->input, \
			*(args->tok_start), i - *(args->tok_start)))) == -1)
			{
				perror("token allocation fail");
				return (-1);
			}
		 // Set the token type to the single operator type based on the current character
		*(args->tokentype) = classify_single_operator((args->input)[i]);
		*(args->tok_start) = i;
	}
	// If the sequence does not form a part of an operator
	else if (!is_part_of_operator(args->input, *(args->tok_start), i))
	{
		// Add the current token to the list as an operator
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
		// Update the token type to the current single operator type
		*(args->tokentype) = classify_single_operator((args->input)[i]);
		// Update the token start index to the current index
		*(args->tok_start) = i;
	}
	// Otherwise, classify the token as a compound operator
	else
		*(args->tokentype) = classify_compound_operator(args->input, \
							*(args->tok_start), i);
	return (0);
}	

// Handles '&&' and_if operator tokens specifically
// Takes token handler arguments and the current index as input
// Checks if the current token type is 'WORD' and adds it to the token list
// Sets the token type to 'AND_IF' and updates the token start index
int	handle_and_if_operator(t_token_handler_args *args, size_t *i)
{
	if (*(args->tokentype) == WORD)
	{
		if (tokenlist_add(args->tokenlist, \
		new_word_token(ft_substr(args->input, \
		*(args->tok_start), *i - *(args->tok_start)))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	else if (*(args->tokentype) >= LPAREN)
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	*(args->tokentype) = AND_IF;
	*(args->tok_start) = *i;
	(*i)++;
	return (0);
}

// Handles spaces and separates tokens
// Takes token handler arguments and the current index as input
// Adds the current token to the token list if the token type is 'WORD'
// Resets the token type to 'UNKNOWN'
int	handle_space(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) == WORD)
	{
		if (tokenlist_add(args->tokenlist, \
		new_word_token(ft_substr(args->input, \
		*(args->tok_start), i - *(args->tok_start)))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	else if (*(args->tokentype) >= LPAREN)
	{
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	*(args->tokentype) = UNKNOWN;
	return (0);
}

// Handles word tokens
// Takes token handler arguments and the current index as input
// Checks if the current token type is an operator and adds it to the token list
// Toggles quote states for single and double quotes
// Sets the token type to 'WORD'
int	handle_word(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) >= LPAREN)
	{
		// If currently an operator, finish it and start a new token
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
		*(args->tok_start) = i;
	}
	else if (*(args->tokentype) == UNKNOWN)
		*(args->tok_start) = i; // Start a new token if none is currently active
	*(args->tokentype) = WORD; // Mark current token as a word
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
	return (0);
}
