/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_fields.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:16:59 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/15 00:17:10 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist	*split_expanded_fields(t_tokenlist *fields)
{
	t_tokenlist	*splited_fields;
	t_toknode	*curr;

	splited_fields = (t_tokenlist *)ft_calloc(1, sizeof(t_tokenlist));
	if (splited_fields == NULL)
		return (NULL);
	curr = fields->head;
	while (curr)
	{
		if (curr->token->quote == NO_QUOTE)
		{
			if (split_single_field(curr->token->str, splited_fields))
			{
				clear_tokenlist(splited_fields);
				return (NULL);
			}
		}
		else
		{
			pop_toknode(fields, curr);
			add_toknode(splited_fields, curr);
		}
		curr = curr->next;
	}
	return (splited_fields);
}

int	split_single_field(char *str, t_tokenlist *splited_fields)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isspace(str[i]))
		{
			if (tokenlist_add(splited_fields, get_splited_field(str, &i)))
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

t_token	*get_splited_field(char *str, size_t *i)
{
	size_t	start;
	t_token	*token;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	token = new_word_token(ft_substr(str, start, *i - start));
	if (token == NULL)
		return (NULL);
	return (token);
}
