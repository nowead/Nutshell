/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:41:17 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/15 00:21:58 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_pathname_in_fields(t_tokenlist *fields)
{
	t_toknode	*curr;

	curr = fields->head;
	while (curr)
	{
		if (expand_pathname_in_single_field(curr))
			return (-1);
		curr = curr->next;
	}
	return (0);
}

int	expand_pathname_in_single_field(t_toknode *curr)
{
	size_t	asterisk_cnt;
	char	**patterns;
	char	*exp_str;

	asterisk_cnt = count_asterisk(curr->token);
	if (asterisk_cnt == 0)
		return (0);
	patterns = (char **)ft_calloc(asterisk_cnt + 2, sizeof(char *));
	if (patterns == NULL)
		return (-1);
	if (fill_patterns(patterns, curr->token))
	{
		ft_free_strs(patterns);
		return (-1);
	}
	exp_str = construct_expanded_pathname(patterns, asterisk_cnt + 1);
	ft_free_strs(patterns);
	if (exp_str == NULL)
		return (-1);
	sort_expanded_pathname(&exp_str);
	free(curr->token->str);
	curr->token->str = exp_str;
	curr->token->quote = NO_QUOTE;
	free(curr->token->is_quoted);
	curr->token->is_quoted = NULL;
	return (0);
}

size_t	count_asterisk(t_token *token)
{
	size_t		cnt;
	size_t		i;

	cnt = 0;
	i = 0;
	while ((token->str)[i])
	{
		if (!(token->is_quoted[i]) && (token->str)[i] == '*')
			cnt++;
		i++;
	}
	return (cnt);
}

int	fill_patterns(char **patterns, t_token *token)
{
	size_t		start;
	size_t		i;
	size_t		j;

	start = 0;
	i = 0;
	j = 0;
	while ((token->str)[i])
	{
		if (!(token->is_quoted)[i] && (token->str)[i] == '*')
		{
			patterns[j] = ft_substr(token->str, start, i - start);
			if (patterns[j] == NULL)
				return (-1);
			i++;
			j++;
			start = i;
		}
		else
			i++;
	}
	patterns[j] = ft_substr(token->str, start, i - start);
	if (patterns[j] == NULL)
		return (-1);
	return (0);
}
