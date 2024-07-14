/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_pathname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:20:18 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/15 00:20:30 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (patterns[i][0] == '\0' && entry[0] == '.')
		return (0);
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
