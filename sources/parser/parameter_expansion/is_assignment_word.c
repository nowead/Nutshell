/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assignment_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:19:08 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 22:44:52 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function determines if a token is an assignment word.
// It checks if the token string starts with '=' (in which case it returns 0).
// Then it searches for an '=' in the string.
// If found, it validates the part before = as a valid name using is_valid_name.
int	is_assignment_word_token(t_token *token)
{
	if (token->type == TOK_ASSIGNMENT_WORD)
		return (1);
	if (token->type != TOK_WORD)
		return (0);
	return (is_assignment_word(token->str));
}

int	is_assignment_word(char *str)
{
	const char	*equalsign_start;

	if (str[0] == '=')
		return (0);
	equalsign_start = ft_strchr(str, '=');
	if (equalsign_start == NULL)
		return (0);
	return (is_valid_name(str, equalsign_start - str));
}

int	is_valid_name(const char *str, size_t len)
{
	size_t	i;

	if (len == 0)
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
