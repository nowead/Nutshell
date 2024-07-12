/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:41:17 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 22:24:44 by seonseo          ###   ########.fr       */
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
	char	*str;
	size_t	asterisk_cnt;
	char	**patterns;
	char	*exp_str;

	str = curr->token->str;
	asterisk_cnt = count_asterisk(str);
	patterns = (char **)ft_calloc(asterisk_cnt + 2, sizeof(char));
	if (patterns == NULL)
		return (-1);
	if (fill_patterns(patterns, str))
	{
		ft_free_strs(patterns);
		return (-1);
	}
	exp_str = construct_expanded_pathname(patterns, asterisk_cnt + 1);
	ft_free_strs(patterns);
	if (exp_str == NULL)
		return (-1);
	free(curr->token->str);
	curr->token->str = exp_str;
	return (0);
}

size_t	count_asterisk(char *str)
{
	t_quotetype	quote;
	size_t		cnt;
	size_t		i;

	quote = NO_QUOTE;
	cnt = 0;
	i = 0;
	while (str[i])
	{
		update_quote_state(str[i], &quote);
		if (str[i] == NO_QUOTE && str[i] == '*')
			cnt++;
		i++;
	}
	return (cnt);
}

void	update_quote_state(char c, t_quotetype *quote)
{
	if (c == '\'')
	{
		if (*quote == NO_QUOTE)
			*quote = SINGLE_QUOTE;
		else if (*quote == SINGLE_QUOTE)
			*quote = NO_QUOTE;
	}
	else if (c == '\"')
	{
		if (*quote == NO_QUOTE)
			*quote = DOUBLE_QUOTE;
		else if (*quote == DOUBLE_QUOTE)
			*quote = NO_QUOTE;
	}
}

int	fill_patterns(char **patterns, char *str)
{
	t_quotetype	quote;
	size_t		start;
	size_t		i;
	size_t		j;

	start = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		update_quote_state(str[i], &quote);
		if (str[i] == NO_QUOTE && str[i] == '*')
		{
			patterns[j] = ft_substr(str, start, i - start);
			if (patterns[j] == NULL)
				return (-1);
			start = i;
			j++;
		}
		i++;
	}
	return (0);
}

char	*construct_expanded_pathname(char **patterns, size_t pattern_cnt)
{
	size_t			i;
	DIR				*dir;
	struct dirent	*entry;
	char			*exp_str;

	exp_str = ft_strdup("");
	if (exp_str == NULL)
		return (NULL);
	dir = opendir(".");
    if (dir == NULL)
		return (NULL);
	i = 0;
	while (i < pattern_cnt)
	{ 
		entry = readdir(dir);
		if (entry == NULL)
		{
			if (closedir(dir) == -1)
				return (NULL);
			return (NULL);
		}
		if (does_entry_match_patterns(entry->d_name, patterns))
			if (concatenate_pathname(&exp_str, entry->d_name))
			{
				free(exp_str);
				if (closedir(dir) == -1)
					return (NULL);
				return (NULL);
			}
		i++;
	}
	if (closedir(dir) == -1)
		return (NULL);
	return (0);
}

int	does_entry_match_patterns(char *entry, char **patterns)
{
	char	*pattern;
	char	*entry_ptr;
	size_t	i;

	entry_ptr = entry;
	i = 0;
	while (patterns[i])
	{
		entry_ptr = ft_strnstr(entry_ptr, patterns[i], ft_strlen(entry_ptr));
		if (entry_ptr == NULL)
			return (0);
		entry_ptr += ft_strlen(patterns[i]);
		i++;
	}
	return (1);
}

int	concatenate_pathname(char **exp_str, char *entry)
{
	char	*tmp;

	tmp = ft_strjoin(*exp_str, entry);
	if (tmp == NULL)
		return (-1);
	free(*exp_str);
	*exp_str = tmp;
	tmp = ft_strjoin(*exp_str, " ");
	if (tmp == NULL)
		return (-1);
	free(*exp_str);
	*exp_str = tmp;
	return (0);
}
