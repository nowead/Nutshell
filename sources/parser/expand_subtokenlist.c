/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_subtokenlist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:36:11 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/26 17:02:35 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_parameters_in_subtoken(t_tokenlist_node *subtokenlist_node, char *envp[]);
static int	expand_parameters_in_string(char **str, char *envp[]);
static int	expand_single_parameter(char **str, size_t *i, char *envp[]);
static void	search_env_end(char *str, size_t *i);
static char	*construct_expanded_str(char *str, size_t start, size_t *i, char *envp[]);
static char	*get_env_value(char *str, size_t start, size_t i, char *envp[]);

int	expand_parameters_in_subtokens(t_tokenlist *subtokenlist, char *envp[])
{
	t_tokenlist_node	*curr;

	curr = subtokenlist->head;
	while (curr)
	{
		if (curr->token->quote != SINGLE_QUOTE && \
		expand_parameters_in_subtoken(curr, envp))
			return (-1);
		curr = curr->next;
	}
	return (0);
}

static int	expand_parameters_in_subtoken(t_tokenlist_node *subtokenlist_node, char *envp[])
{
	char		*str;

	str = subtokenlist_node->token->str;
	if (expand_parameters_in_string(&str, envp) == -1)
		return (-1);
	subtokenlist_node->token->str = str;
	return (0);
}

static int	expand_parameters_in_string(char **str, char *envp[])
{
	size_t		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (expand_single_parameter(str, &i, envp) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

static int	expand_single_parameter(char **str, size_t *i, char *envp[])
{
	size_t	start;
	char	*exp_str;

	start = *i;
	search_env_end(*str, i);
	if (ft_isalnum((*str)[start + 1]))
	{
		exp_str = construct_expanded_str(*str, start, i, envp);
		if (exp_str == NULL)
			return (-1);
		free(*str);
		*str = exp_str;
	}
	return (0);
}

static void	search_env_end(char *str, size_t *i)
{
	(*i)++;
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return;
	}
	while (ft_isalnum(str[*i]))
		(*i)++;
}

static char	*construct_expanded_str(char *str, size_t start, size_t *i, char *envp[])
{
	char	*env_value;
	char	*exp_str;
	size_t	exp_len;
	size_t	env_key_len;

	env_key_len = *i - start;
	env_value = get_env_value(str, start, *i, envp);
	if (env_value == NULL)
		return (NULL);
	exp_len = ft_strlen(str) + ft_strlen(env_value) - env_key_len;
	exp_str = (char *)malloc(sizeof(char) * exp_len + 1);
	if (exp_str == NULL)
		return (NULL);
	ft_strlncpy(exp_str, str, exp_len + 1, start);
	ft_strlcat(exp_str, env_value, exp_len + 1);
	ft_strlcat(exp_str, &str[*i], exp_len + 1);
	return (exp_str);
}

static char	*get_env_value(char *str, size_t start, size_t i, char *envp[])
{
	char	*key;
	char	*value;

	key = ft_substr(str, start + 1, i - start - 1);
	if (key == NULL)
		return (NULL);
	value = ft_getenv(key, envp);
	free(key);
	if (value == NULL)
		return ("");
	return (value);
}
