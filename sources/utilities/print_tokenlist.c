/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokenlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:13:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/01 17:31:00 by seonseo          ###   ########.fr       */
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
		if (curr->token->is_quoted)
		{
			if (ft_printf("%s:", tokentype_str) == -1)
				return (-1);
			ft_printf("quote:%d:", curr->token->quote);
			if (print_int_array(curr->token->is_quoted, \
			ft_strlen(curr->token->str)) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	return (0);
}

int	print_int_array(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_printf("%d", arr[i]) == -1)
			return (-1);
		i++;
	}
	if (ft_printf("\n") == -1)
		return (-1);
	return (0);
}
