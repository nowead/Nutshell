/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 01:04:09 by seonseo          ###   ########.fr       */
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

	subtokenlist = split_into_subtokens(toknode);
	if (subtokenlist == NULL)
		return (-1);
	if (expand_parameters_in_subtokens(subtokenlist, shell_ctx))
	{
		clear_tokenlist(subtokenlist);
		return (-1);
	}
	fields = split_subtokens_into_fields(subtokenlist);
	clear_tokenlist(subtokenlist);
	if (fields == NULL)
		return (-1);
	if (fields->size != 0)
		insert_fields_into_tokenlist(tokenlist, toknode, fields);
	else
		pop_toknode(tokenlist, toknode);
	free_toknode(toknode);
	free(fields);
	return (0);
}
