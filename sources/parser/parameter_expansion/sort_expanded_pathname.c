/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_expanded_pathname.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:22:01 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/04 02:57:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sort_expanded_pathname(char **exp_str)
{
	char	**splited;

	splited = ft_split(*exp_str, ' ');
	if (splited == NULL)
		return (-1);
	ft_string_sort(splited, ft_strslen(splited));
	free(*exp_str);
	*exp_str = ft_strsjoin(splited, ' ');
	if (*exp_str == NULL)
	{
		ft_free_strs(splited);
		return (-1);
	}
	ft_free_strs(splited);
	return (0);
}

void	ft_string_sort(char **strs, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	min;

	i = 0;
	while (i < len - 1)
	{
		min = i;
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(strs[j], strs[min]) < 0)
				min = j;
			j++;
		}
		if (min != i)
			ft_swap_strings(&strs[i], &strs[min]);
		i++;
	}
}

void	ft_swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	*ft_strsjoin(char **strs, char c)
{
	char	*joined;
	size_t	len;
	size_t	i;
	size_t	j;

	len = get_joined_len(strs);
	joined = (char *)ft_calloc(len + ft_strslen(strs), sizeof(char));
	if (joined == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (strs[i])
	{
		ft_strlcpy(joined + j, strs[i], ft_strlen(strs[i]) + 1);
		j += ft_strlen(strs[i]);
		if (strs[i + 1])
			joined[j++] = c;
		i++;
	}
	return (joined);
}

size_t	get_joined_len(char **strs)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (strs[i])
	{
		len += ft_strlen(strs[i]);
		i++;
	}
	return (len);
}
