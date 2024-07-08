/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token_creation_handler.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:02:42 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 22:08:55 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handles operator tokens
// Takes token handler arguments and the current index as input
// Classifies and sets the token type to the appropriate single operator
// Adds the token to the token list if necessary
int	handle_operator(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) < TOK_LPAREN)
	{
		if (handle_word_to_operator(args, i) == -1)
			return (-1);
	}
	else if (!is_part_of_operator(args->input, *(args->tok_start), i))
	{
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
		*(args->tokentype) = classify_single_operator((args->input)[i]);
		*(args->tok_start) = i;
	}
	else
		*(args->tokentype) = \
		classify_compound_operator(args->input, *(args->tok_start), i);
	return (0);
}

int	handle_word_to_operator(t_token_handler_args *args, size_t i)
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
	*(args->tokentype) = classify_single_operator((args->input)[i]);
	*(args->tok_start) = i;
	return (0);
}

// Handles '&&' and_if operator tokens specifically
// Takes token handler arguments and the current index as input
// Checks if the current token type is 'TOK_WORD' and adds it to the token list
// Sets the token type to 'TOK_AND_IF' and updates the token start index
int	handle_and_if_operator(t_token_handler_args *args, size_t *i)
{
	if (*(args->tokentype) == TOK_WORD)
	{
		if (tokenlist_add(args->tokenlist, \
		new_word_token(ft_substr(args->input, \
		*(args->tok_start), *i - *(args->tok_start)))) == -1)
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
	*(args->tokentype) = TOK_AND_IF;
	*(args->tok_start) = *i;
	(*i)++;
	return (0);
}
