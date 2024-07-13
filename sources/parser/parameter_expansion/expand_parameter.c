/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 22:57:35 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_parameter(t_tokenlist *tokenlist, t_shell_ctx *shell_ctx)
{
	t_toknode	*curr;
	t_toknode	*prev;

	curr = tokenlist->head;
	while (curr)
	{
		if (curr->token->type == TOK_WORD)
		{
			prev = curr;
			curr = curr->next;
			if (expand_parameters_in_a_token(prev, tokenlist, shell_ctx))
				return (-1);
		}
		else
			curr = curr->next;
	}
	return (0);
}

int	expand_parameters_in_a_token(t_toknode *toknode, t_tokenlist *tokenlist, \
t_shell_ctx *shell_ctx)
{
	t_tokenlist			*subtokenlist;
	t_tokenlist			*fields;
	t_tokenlist			*splited_fields;

	subtokenlist = split_into_subtokens(toknode);
	if (subtokenlist == NULL)
		return (-1);
	if (expand_parameters_in_subtokens(subtokenlist, shell_ctx))
	{
		clear_tokenlist(subtokenlist);
		return (-1);
	}
	if (save_quote_in_subtokens(subtokenlist))
	{
		clear_tokenlist(subtokenlist);
		return (-1);
	}
	fields = split_subtokens_into_fields(subtokenlist);
	clear_tokenlist(subtokenlist);
	if (fields == NULL)
		return (-1);
	if (expand_pathname_in_fields(fields))
	{
		free(fields);
		return (-1);
	}
	splited_fields = split_expanded_fields(fields);
	clear_tokenlist(fields);
	if (splited_fields->size != 0)
		insert_fields_into_tokenlist(tokenlist, toknode, fields);
	else
		pop_toknode(tokenlist, toknode);
	free_toknode(toknode);
	return (0);
}

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
