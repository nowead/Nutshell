/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subtokenlist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:36:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 22:05:50 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_parameters_in_subtokens(t_tokenlist *subtokenlist, \
t_shell_ctx *shell_ctx)
{
	t_toknode	*curr;

	curr = subtokenlist->head;
	while (curr)
	{
		if (curr->token->quote != SINGLE_QUOTE && \
		expand_parameters_in_subtoken(curr, shell_ctx))
			return (-1);
		curr = curr->next;
	}
	return (0);
}

int	expand_parameters_in_subtoken(t_toknode *subtoknode, \
t_shell_ctx *shell_ctx)
{
	char		*str;

	str = subtoknode->token->str;
	if (expand_parameters_in_string(&str, shell_ctx) == -1)
		return (-1);
	subtoknode->token->str = str;
	return (0);
}
