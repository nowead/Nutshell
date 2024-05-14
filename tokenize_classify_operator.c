/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_classify_operator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:23:41 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/14 20:51:16 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

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
	int	len;

	len = i - tok_start + 1;
	if (len == 2)
	{
		if (ft_strncmp("&&", &input[tok_start], len) == 0 || \
			ft_strncmp("||", &input[tok_start], len) == 0 || \
			ft_strncmp("<<", &input[tok_start], len) == 0 || \
			ft_strncmp(">>", &input[tok_start], len) == 0)
			return (1);
	}
	return (0);
}

// Classifies a single character operator
t_tokentype	classify_single_operator(char c)
{
	if (c == '<')
		return (TOK_LESS);
	else if (c == '>')
		return (TOK_GREAT);
	else if (c == '|')
		return (TOK_PIPE);
	return (TOK_UNKNOWN);
}

// Classifies a compound operator
t_tokentype	classify_compound_operator(const char *input, \
size_t tok_start, size_t i)
{
	int	len;

	len = i - tok_start + 1;
	if (ft_strncmp("&&", &input[tok_start], len) == 0)
		return (TOK_AND_IF);
	else if (ft_strncmp("||", &input[tok_start], len) == 0)
		return (TOK_OR_IF);
	else if (ft_strncmp("<<", &input[tok_start], len) == 0)
		return (TOK_DLESS);
	else if (ft_strncmp(">>", &input[tok_start], len) == 0)
		return (TOK_DGREAT);
	return (TOK_UNKNOWN);
}
