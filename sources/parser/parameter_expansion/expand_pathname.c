/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pathname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:41:17 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 22:35:36 by seonseo          ###   ########.fr       */
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

char	*construct_expanded_pathname(char **patterns, size_t pattern_cnt)
{
	int				is_match_found;
	DIR				*dir;
	struct dirent	*entry;
	char			*exp_str;

	exp_str = ft_strdup("");
	if (exp_str == NULL)
		return (NULL);
	dir = opendir(".");
    if (dir == NULL)
		return (NULL);
	is_match_found = 0;
	while (1)
	{ 
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (does_entry_match_patterns(entry->d_name, patterns, pattern_cnt))
		{
			if (is_match_found != 0 && concatenate_space(&exp_str))
			{
				free(exp_str);
				if (closedir(dir) == -1)
					return (NULL);
			}
			if (concatenate_pathname(&exp_str, entry->d_name))
			{
				free(exp_str);
				if (closedir(dir) == -1)
					return (NULL);
			}
			is_match_found = 1;
		}
	}
	if (closedir(dir) == -1)
		return (NULL);
	return (exp_str);
}

int	does_entry_match_patterns(char *entry, char **patterns, size_t pattern_cnt)
{
	char	*pattern;
	char	*entry_ptr;
	size_t	i;

	entry_ptr = entry;
	i = 0;
	if (ft_strncmp(entry_ptr, patterns[i], ft_strlen(patterns[i])))
		return (0);
	entry_ptr += ft_strlen(patterns[i]);
	i++;
	while (i < pattern_cnt - 1)
	{
		entry_ptr = ft_strnstr(entry_ptr, patterns[i], ft_strlen(entry_ptr));
		if (entry_ptr == NULL)
			return (0);
		entry_ptr += ft_strlen(patterns[i]);
		i++;
	}
	if (ft_strncmp(entry + ft_strlen(entry) - ft_strlen(patterns[i]), \
	patterns[i], ft_strlen(patterns[i])))
		return (0);
	return (1);
}

int	concatenate_space(char **exp_str)
{
	char	*tmp;

	tmp = ft_strjoin(*exp_str, " ");
	if (tmp == NULL)
		return (-1);
	free(*exp_str);
	*exp_str = tmp;
	return (0);
}

int	concatenate_pathname(char **exp_str, char *entry)
{
	char	*tmp;

	tmp = ft_strjoin(*exp_str, entry);
	if (tmp == NULL)
		return (-1);
	free(*exp_str);
	*exp_str = tmp;
	return (0);
}
