/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_subtokens_into_fields.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:21:47 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:52:59 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist	*split_subtokens_into_fields(t_tokenlist *subtokenlist)
{
	t_toknode	*curr_subtok;
	t_tokenlist	*fields;

	fields = (t_tokenlist *)ft_calloc(1, sizeof(t_tokenlist));
	if (fields == NULL)
		return (NULL);
	curr_subtok = subtokenlist->head;
	while (curr_subtok)
	{
		if (curr_subtok->token->quote == NO_QUOTE)
		{
			if (handle_no_quote_token(&curr_subtok, fields))
				return (clear_tokenlist(fields));
		}
		else
		{
			if (handle_quote_token(subtokenlist, &curr_subtok, fields))
				return (clear_tokenlist(fields));
		}
	}
	return (fields);
}

int	handle_quote_token(t_tokenlist *subtokenlist, t_toknode **curr_subtok, \
t_tokenlist *fields)
{
	t_toknode	*prev_subtok;
	t_token		*fields_back_token;

	prev_subtok = *curr_subtok;
	*curr_subtok = (*curr_subtok)->next;
	if (fields->back && fields->back->token->quote != NO_QUOTE)
	{
		fields_back_token = fields->back->token;
		fields->back->token = \
		merge_two_tokens(fields->back->token, prev_subtok->token);
		free(fields_back_token);
		if (fields->back->token == NULL)
			return (-1);
	}
	else
	{
		pop_toknode(subtokenlist, prev_subtok);
		add_toknode(fields, prev_subtok);
	}
	return (0);
}

t_token	*merge_two_tokens(t_token *token1, t_token *token2)
{
	char	*merged_str;
	size_t	merged_str_len;
	t_token	*merged_token;

	merged_str_len = ft_strlen(token1->str) + ft_strlen(token2->str);
	merged_str = (char *)ft_calloc(merged_str_len + 1, sizeof(char));
	if (merged_str == NULL)
		return (NULL);
	ft_strlcat(merged_str, token1->str, merged_str_len + 1);
	ft_strlcat(merged_str, token2->str, merged_str_len + 1);
	merged_token = new_word_token(merged_str);
	if (merged_token == NULL)
		return (NULL);
	merged_token->quote = MERGED_QUOTE;
	return (merged_token);
}
