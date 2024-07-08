/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:13:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 17:14:07 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_tokenlist(t_tokenlist *tokenlist)
{
	t_toknode	*curr;
	const char	*tokentype_str;

	curr = tokenlist->head;
	while (curr)
	{
		tokentype_str = get_token_type_string(curr->token->type);
		if (ft_printf("%s:", tokentype_str) == -1)
			return (-1);
		ft_printf("quote:%d:", curr->token->quote);
		if (ft_printf("%s\n", curr->token->str) == -1)
			return (-1);
		curr = curr->next;
	}
	return (0);
}
