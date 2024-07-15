/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter_in_a_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:16:47 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/15 15:46:55 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_parameters_in_a_token(t_toknode *toknode, t_tokenlist *tokenlist, \
t_shell_ctx *shell_ctx)
{
	t_tokenlist	*subtokenlist;
	t_tokenlist	*fields;
	t_tokenlist	*splited_fields;

	subtokenlist = split_into_subtokens_and_expand(toknode, shell_ctx);
	if (subtokenlist == NULL)
		return (-1);
	fields = save_quote_and_split_into_fields(subtokenlist);
	if (fields == NULL)
		return (-1);
	splited_fields = expand_pathname_and_split_fields(fields);
	if (splited_fields == NULL)
		return (-1);
	return (insert_or_pop_fields(tokenlist, toknode, splited_fields));
}

t_tokenlist	*split_into_subtokens_and_expand(t_toknode *toknode, \
t_shell_ctx *shell_ctx)
{
	t_tokenlist	*subtokenlist;

	subtokenlist = split_into_subtokens(toknode);
	if (subtokenlist == NULL)
		return (NULL);
	if (expand_parameters_in_subtokens(subtokenlist, shell_ctx))
	{
		clear_tokenlist(subtokenlist);
		return (NULL);
	}
	return (subtokenlist);
}

t_tokenlist	*save_quote_and_split_into_fields(t_tokenlist *subtokenlist)
{
	t_tokenlist	*fields;

	if (save_quote_in_subtokens(subtokenlist))
	{
		clear_tokenlist(subtokenlist);
		return (NULL);
	}
	fields = split_subtokens_into_fields(subtokenlist);
	clear_tokenlist(subtokenlist);
	return (fields);
}

t_tokenlist	*expand_pathname_and_split_fields(t_tokenlist *fields)
{
	t_tokenlist	*splited_fields;

	if (expand_pathname_in_fields(fields))
	{
		clear_tokenlist(fields);
		return (NULL);
	}
	splited_fields = split_expanded_fields(fields);
	clear_tokenlist(fields);
	return (splited_fields);
}

int	insert_or_pop_fields(t_tokenlist *tokenlist, t_toknode *toknode, \
t_tokenlist *splited_fields)
{
	if (splited_fields->size != 0)
		insert_fields_into_tokenlist(tokenlist, toknode, splited_fields);
	else
		pop_toknode(tokenlist, toknode);
	free_toknode(toknode);
	free(splited_fields);
	return (0);
}
