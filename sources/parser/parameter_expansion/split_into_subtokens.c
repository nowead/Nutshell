/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_subtokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:21:29 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 17:04:10 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*split_quoted_token(char *str, size_t *i);
static t_token	*split_unquoted_token(char *str, size_t *i);

t_tokenlist	*split_into_subtokens(t_toknode *toknode)
{
	size_t		i;
	char		*str;
	t_tokenlist	*subtokenlist;

	subtokenlist = (t_tokenlist *)ft_calloc(1, sizeof(t_tokenlist));
	if (subtokenlist == NULL)
		return (NULL);
	str = toknode->token->str;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (tokenlist_add(subtokenlist, split_quoted_token(str, &i)))
				return (clear_tokenlist(subtokenlist));
		}
		else if (tokenlist_add(subtokenlist, split_unquoted_token(str, &i)))
			return (clear_tokenlist(subtokenlist));
	}
	return (subtokenlist);
}

static t_token	*split_quoted_token(char *str, size_t *i)
{
	char		quote;
	t_quotetype	quotetype;
	size_t		start;
	t_token		*token;

	quote = str[*i];
	if (quote == '\'')
		quotetype = SINGLE_QUOTE;
	else if (quote == '\"')
		quotetype = DOUBLE_QUOTE;
	start = *i;
	(*i)++;
	while (str[*i] != quote)
		(*i)++;
	token = new_word_token(ft_substr(str, start, *i - start + 1));
	if (token == NULL)
		return (NULL);
	(*i)++;
	token->quote = quotetype;
	return (token);
}

static t_token	*split_unquoted_token(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	return (new_word_token(ft_substr(str, start, *i - start)));
}
