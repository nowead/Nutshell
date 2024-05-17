/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assignment_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:19:08 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/17 22:01:24 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static int	is_valid_name(const char *str, size_t len);

// This function determines if a token is an assignment word.
// It checks if the token string starts with '=' (in which case it returns 0).
// Then it searches for an '=' in the string.
// If found, it validates the part before = as a valid name using is_valid_name.
int	is_assignment_word(t_token *token)
{
	const char	*equalsign_start;

	if ((token->str)[0] == '=')
		return (0);
	equalsign_start = ft_strchr(token->str, '=');
	if (equalsign_start == NULL)
		return (0);
	if (is_valid_name(token->str, equalsign_start - token->str))
		return (1);
	return (0);
}

// This function checks if a given string (of specified length) is a valid name.
// It must not be empty, must not start with a digit,
// and must consist of alphanumeric characters or underscores.
static int	is_valid_name(const char *str, size_t len)
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
