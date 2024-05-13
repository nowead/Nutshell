/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:57:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/13 15:29:32 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

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
				tokenize_err_exit(args->tokenlist, "token allocation fail");
		*(args->tokentype) = TOK_OPERATOR;
		*(args->tok_start) = i;
	}
	else if (!is_part_of_operator(args->input, *(args->tok_start), i))
	{
		// Start a new operator token if it's not a continuation of the current operator
		if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
		ft_substr(args->input, *(args->tok_start), \
		i - *(args->tok_start)))) == -1)
			tokenize_err_exit(args->tokenlist, "token allocation fail");
		*(args->tok_start) = i;
	}
}

// Handles '&&' and_if operator tokens specifically
void	handle_and_if_operator(t_token_handler_args *args, size_t *i)
{
	// Finish the current token if it exists and is not of type 'unknown'
	if (i > 0 && *(args->tokentype) != TOK_UNKNOWN)
		if (tokenlist_add(args->tokenlist, new_token(*(args->tokentype), \
		ft_substr(args->input, *(args->tok_start), \
		*i - *(args->tok_start)))) == -1)
			tokenize_err_exit(args->tokenlist, "token allocation fail");
	// Start a new operator token and increase index to the end of the token
	*(args->tokentype) = TOK_OPERATOR;
	*(args->tok_start) = *i;
	(*i)++;
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
