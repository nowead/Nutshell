/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_quote_in_subtokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:50:50 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 21:31:04 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_quote_in_subtokens(t_tokenlist *subtokenlist)
{
	t_toknode	*curr;

	curr = subtokenlist->head;
	while (curr)
	{
		if (save_quote_in_a_token(curr))
			return (-1);
		curr = curr->next;
	}
	return (0);
}

int	save_quote_in_a_token(t_toknode *toknode)
{
	int			**is_quoted;
	size_t		str_len;

	is_quoted = &(toknode->token->is_quoted);
	str_len = ft_strlen(toknode->token->str);
	*is_quoted = (int *)ft_calloc(str_len, sizeof(int));
	if (*is_quoted == NULL)
		return (-1);
	if (toknode->token->quote == SINGLE_QUOTE || \
	toknode->token->quote == DOUBLE_QUOTE)
		fill_int_array(*is_quoted, str_len, 1);
	return (0);
}

void	fill_int_array(int *arr, size_t len, int value)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		arr[i] = value;
		i++;
	}
}
