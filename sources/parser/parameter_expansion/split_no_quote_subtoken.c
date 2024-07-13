/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_no_quote_subtoken.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:50:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 21:04:37 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_no_quote_token(t_toknode **curr_subtok, t_tokenlist *fields)
{
	size_t	i;
	char	*str;
	int		is_space;

	str = (*curr_subtok)->token->str;
	i = 0;
	if (fields->back && !ft_isspace(str[i]))
		if (handle_first_field(str, &i, fields) == -1)
			return (-1);
	while (str[i])
		if (handle_middle_field(str, &i, fields, &is_space) == -1)
			return (-1);
	if ((*curr_subtok)->next && is_space == 0)
		if (handle_last_field(fields, curr_subtok) == -1)
			return (-1);
	*curr_subtok = (*curr_subtok)->next;
	return (0);
}

int	handle_first_field(char *str, size_t *i, t_tokenlist *fields)
{
	t_token	*fields_back_token;
	t_token	*first_field;

	fields_back_token = fields->back->token;
	first_field = get_field(str, i);
	fields->back->token = merge_two_tokens(fields->back->token, first_field);
	free_token(fields_back_token);
	free_token(first_field);
	if (fields->back->token == NULL)
		return (-1);
	return (0);
}

int	handle_middle_field(char *str, size_t *i, t_tokenlist *fields, \
int *is_space)
{
	*is_space = 1;
	if (!ft_isspace(str[*i]))
	{
		*is_space = 0;
		if (tokenlist_add(fields, get_field(str, i)))
			return (-1);
	}
	else
		(*i)++;
	return (0);
}

int	handle_last_field(t_tokenlist *fields, t_toknode **curr_subtok)
{
	t_token	*fields_back_token;

	fields_back_token = fields->back->token;
	fields->back->token = \
	merge_two_tokens(fields->back->token, (*curr_subtok)->next->token);
	free_token(fields_back_token);
	if (fields->back->token == NULL)
		return (-1);
	*curr_subtok = (*curr_subtok)->next;
	return (0);
}

t_token	*get_field(char *str, size_t *i)
{
	size_t	start;
	t_token	*token;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	token = new_word_token(ft_substr(str, start, *i - start));
	if (token == NULL)
		return (NULL);
	token->is_quoted = (int *)ft_calloc(ft_strlen(token->str), sizeof(int));
	if (token->is_quoted == NULL)
	{
		free_token(token);
		return (NULL);
	}
	fill_int_array(token->is_quoted, ft_strlen(token->str), 0);
	return (token);
}
