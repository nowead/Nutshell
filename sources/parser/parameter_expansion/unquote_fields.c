/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_fields.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:33:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 20:19:51 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unquote_fields(t_tokenlist *fields)
{
	t_toknode	*curr;

	curr = fields->head;
	while (curr)
	{
		if (unquote_single_field(curr))
			return (-1);
		curr = curr->next;
	}
	return (0);
}

int	unquote_single_field(t_toknode *curr)
{
	char	*str;
	char	*unquoted_str;
	size_t	unquoted_len;


	str = curr->token->str;
	unquoted_len = get_unquoted_len(str);
	unquoted_str = (char *)ft_calloc(unquoted_len + 1, sizeof(char));
	if (unquoted_str == NULL)
		return (-1);
	copy_str_to_unquoted_str(unquoted_str, str);
	free(curr->token->str);
	curr->token->str = unquoted_str;
	return (0);
}

size_t	get_unquoted_len(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			len++;
		i++;
	}
	return (len);
}

void	copy_str_to_unquoted_str(char *unquoted_str, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] != '\'' && str[j] != '\"')
		{
			unquoted_str[i] = str[j];
			i++;
		}
		j++;
	}
	unquoted_str[i] = '\0';
}
