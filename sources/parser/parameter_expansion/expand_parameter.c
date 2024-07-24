/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/24 21:07:06 by seonseo          ###   ########.fr       */
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
			if (is_prev_dless(prev))
			{
				if (unquote_a_token(prev))
					return (-1);
			}
			else if (expand_parameters_in_a_token(prev, tokenlist, shell_ctx))
				return (-1);
		}
		else
			curr = curr->next;
	}
	return (0);
}

int	is_prev_dless(t_toknode *curr)
{
	if (curr->prev && curr->prev->token->type == TOK_DLESS)
		return (1);
	return (0);
}
