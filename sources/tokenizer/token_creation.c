/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:35:40 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 21:35:57 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist	*new_tokenlist(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = (t_tokenlist *)ft_calloc(1, sizeof(t_tokenlist));
	return (tokenlist);
}

t_token	*new_word_token(char *str)
{
	t_token	*new_token;

	if (str == NULL)
		return (NULL);
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
	{
		free(str);
		return (NULL);
	}
	new_token->type = TOK_WORD;
	new_token->str = str;
	return (new_token);
}

t_token	*new_operator_token(t_tokentype type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = type;
	return (new_token);
}

t_toknode	*new_toknode(t_token *token)
{
	t_toknode	*toknode;

	toknode = (t_toknode *)ft_calloc(1, sizeof(t_toknode));
	if (toknode == NULL)
		return (NULL);
	toknode->token = token;
	return (toknode);
}
