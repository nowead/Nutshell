/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_a_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:41:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/26 21:16:09 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unquote_a_token(t_toknode *curr)
{
	char	*str;
	char	*unquoted_str;
	size_t	unquoted_len;

	str = curr->token->str;
	unquoted_len = get_unquoted_len(str);
	unquoted_str = (char *)ft_calloc(unquoted_len + 1, sizeof(char));
	if (unquoted_str == NULL)
		return (-1);
	copy_str_to_unquoted_str(unquoted_str, str);
	free(curr->token->str);
	curr->token->str = unquoted_str;
	return (0);
}

size_t	get_unquoted_len(char *str)
{
	size_t		i;
	size_t		len;
	t_quotetype	quotetype;

	quotetype = NO_QUOTE;
	i = 0;
	len = 0;
	while (str[i])
	{
		if (!is_real_quote(str, i, quotetype))
			len++;
		evaluate_quotetype(str, i, &quotetype);
		i++;
	}
	return (len);
}

void	copy_str_to_unquoted_str(char *unquoted_str, char *str)
{
	size_t		i;
	size_t		j;
	t_quotetype	quotetype;

	quotetype = NO_QUOTE;
	i = 0;
	j = 0;
	while (str[j])
	{
		if (!is_real_quote(str, j, quotetype))
		{
			unquoted_str[i] = str[j];
			i++;
		}
		evaluate_quotetype(str, j, &quotetype);
		j++;
	}
	unquoted_str[i] = '\0';
}

void	evaluate_quotetype(const char *str, const size_t i, \
t_quotetype *quotetype)
{
	if (str[i] == '\'')
	{
		if (*quotetype == NO_QUOTE)
			*quotetype = SINGLE_QUOTE;
		else if (*quotetype == SINGLE_QUOTE)
			*quotetype = NO_QUOTE;
		else if (*quotetype == DOUBLE_QUOTE)
			*quotetype = DOUBLE_QUOTE;
	}
	else if (str[i] == '\"')
	{
		if (*quotetype == NO_QUOTE)
			*quotetype = DOUBLE_QUOTE;
		else if (*quotetype == DOUBLE_QUOTE)
			*quotetype = NO_QUOTE;
		else if (*quotetype == SINGLE_QUOTE)
			*quotetype = SINGLE_QUOTE;
	}
}

int	is_real_quote(const char *str, const size_t i, const t_quotetype quotetype)
{
	if (str[i] == '\'')
	{
		if (quotetype == NO_QUOTE)
			return (1);
		else if (quotetype == SINGLE_QUOTE)
			return (1);
		else if (quotetype == DOUBLE_QUOTE)
			return (0);
	}
	else if (str[i] == '\"')
	{
		if (quotetype == NO_QUOTE)
			return (1);
		else if (quotetype == DOUBLE_QUOTE)
			return (1);
		else if (quotetype == SINGLE_QUOTE)
			return (0);
	}
	return (0);
}
