/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/04 22:32:06 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_parameter(t_tokenlist *tokenlist, char *envp[])
{
	t_tokenlist_node	*curr;
	t_tokenlist_node	*prev;

	curr = tokenlist->head;
	while (curr)
	{
		if (curr->token->type == WORD)
		{
			prev = curr;
			curr = curr->next;
			if (expand_parameters_in_a_token(prev, tokenlist, envp))
				return (-1);
		}
		else
			curr = curr->next;
	}
	return (0);
}

int	expand_parameters_in_a_token(t_tokenlist_node *tokenlist_node, t_tokenlist *tokenlist, char *envp[])
{
	t_tokenlist			*subtokenlist;
	t_tokenlist			*fields;

	subtokenlist = split_into_subtokens(tokenlist_node);
	if (subtokenlist == NULL)
		return (-1);
	if (expand_parameters_in_subtokens(subtokenlist, envp))
		return ((int)clear_tokenlist(subtokenlist));
	printf("\n\n==subtokenlist==\n");
	print_tokenlist(subtokenlist);
	fields = split_subtokens_into_fields(subtokenlist);
	clear_tokenlist(subtokenlist);
	printf("\n\n==fields==\n");
	print_tokenlist(fields);
	if (fields == NULL)
		return (-1);
	if (fields->size != 0)
		insert_fields_into_tokenlist(tokenlist, tokenlist_node, fields);
	else
		pop_tokenlist_node(tokenlist, tokenlist_node);
	free_tokenlist_node(tokenlist_node);
	free(fields);
	return (0);
}

t_tokenlist	*split_subtokens_into_fields(t_tokenlist *subtokenlist)
{
	t_tokenlist_node	*curr_subtok;
	t_tokenlist			*fields;

	fields = (t_tokenlist *)ft_calloc(1, sizeof(t_tokenlist));
	if (fields == NULL)
		return (NULL);
	curr_subtok = subtokenlist->head;
	while (curr_subtok)
	{
		if (curr_subtok->token->quote == NO_QUOTE)
		{
			if (handle_no_quote_token(&curr_subtok, fields))
				return (NULL);
		}
		else
			handle_quote_token(subtokenlist, &curr_subtok, fields);
	}
	return (fields);
}

int	handle_no_quote_token(t_tokenlist_node **curr_subtok, t_tokenlist *fields)
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

int	handle_middle_field(char *str, size_t *i, t_tokenlist *fields, int *is_space)
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

int	handle_last_field(t_tokenlist *fields, t_tokenlist_node **curr_subtok)
{
	t_token	*fields_back_token;

	fields_back_token = fields->back->token;
	fields->back->token = merge_two_tokens(fields->back->token, (*curr_subtok)->next->token);
	free_token(fields_back_token);
	if (fields->back->token == NULL)
		return (-1);
	*curr_subtok = (*curr_subtok)->next;
	return (0);
}

void	handle_quote_token(t_tokenlist *subtokenlist, t_tokenlist_node **curr_subtok, t_tokenlist *fields)
{
	t_tokenlist_node	*prev_subtok;
	t_token				*fields_back_token;

	prev_subtok = *curr_subtok;
	*curr_subtok = (*curr_subtok)->next;
	if (fields->back && fields->back->token->quote != NO_QUOTE)
	{
		fields_back_token = fields->back->token;
		fields->back->token = merge_two_tokens(fields->back->token, prev_subtok->token);
		free(fields_back_token);
	}
	else
	{
		pop_tokenlist_node(subtokenlist, prev_subtok);
		tokenlist_add_node(fields, prev_subtok);
	}
}

t_token	*merge_two_tokens(t_token *token1, t_token *token2)
{
	char	*merged_str;
	size_t	merged_str_len;

	merged_str_len = ft_strlen(token1->str) + ft_strlen(token2->str);
	merged_str = (char *)ft_calloc(merged_str_len + 1, sizeof(char));
	if (merged_str == NULL)
		return (NULL);
	ft_strlcat(merged_str, token1->str, merged_str_len + 1);
	ft_strlcat(merged_str, token2->str, merged_str_len + 1);
	return (new_word_token(merged_str));
}

t_token	*get_field(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	return (new_word_token(ft_substr(str, start, *i - start)));
}

void	insert_fields_into_tokenlist(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node, t_tokenlist *fields)
{
	t_tokenlist_node	*prev;
	t_tokenlist_node	*next;

	prev = tokenlist_node->prev;
	next = tokenlist_node->next;
	if (prev != NULL)
	{
		prev->next = fields->head;
		fields->head->prev = prev;
	}
	else
		tokenlist->head = fields->head;
	if (next != NULL)
	{
		next->prev = fields->back;
		fields->back->next = next;
	}
	else
		tokenlist->back = fields->back;
}
