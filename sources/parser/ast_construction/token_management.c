/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:31:41 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 20:31:51 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_next_token(t_toknode **toknode)
{
	(*toknode) = (*toknode)->next;
}

t_tokentype	curr_tokentype(t_toknode **toknode)
{
	if (*toknode == NULL || (*toknode)->token == NULL)
		return (TOK_UNKNOWN);
	return ((*toknode)->token->type);
}

t_token	*curr_token(t_toknode **toknode)
{
	if (*toknode == NULL)
		return (NULL);
	return ((*toknode)->token);
}
