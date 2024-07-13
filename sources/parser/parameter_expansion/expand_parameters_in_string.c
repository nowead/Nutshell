/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters_in_string.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:59:50 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 22:31:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*construct_expanded_str(char *str, size_t start, size_t *i, \
t_shell_ctx *shell_ctx);

int	expand_parameters_in_string(char **str, t_shell_ctx *shell_ctx)
{
	size_t		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (expand_single_parameter(str, &i, shell_ctx) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	expand_single_parameter(char **str, size_t *i, \
t_shell_ctx *shell_ctx)
{
	size_t	start;
	char	*exp_str;

	start = *i;
	search_env_end(*str, i);
	if (ft_isalnum((*str)[start + 1]) || (*str)[start + 1] == '?')
	{
		exp_str = construct_expanded_str(*str, start, i, shell_ctx);
		if (exp_str == NULL)
			return (-1);
		free(*str);
		*str = exp_str;
	}
	return (0);
}

void	search_env_end(char *str, size_t *i)
{
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return ;
	}
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return ;
	}
	while (ft_isalnum(str[*i]))
		(*i)++;
}

static char	*construct_expanded_str(char *str, size_t start, size_t *i, \
t_shell_ctx *shell_ctx)
{
	char	*env_value;
	char	*exp_str;
	size_t	exp_len;
	size_t	env_key_len;

	env_key_len = *i - start;
	if (str[start + 1] == '?')
		env_value = ft_itoa(shell_ctx->exit_status);
	else
		env_value = ft_strdup(get_env_value(str, start, *i, shell_ctx->envp));
	if (env_value == NULL)
		return (NULL);
	exp_len = ft_strlen(str) + ft_strlen(env_value) - env_key_len;
	exp_str = (char *)malloc(sizeof(char) * exp_len + 1);
	if (exp_str == NULL)
	{
		free(env_value);
		return (NULL);
	}
	ft_strlncpy(exp_str, str, exp_len + 1, start);
	ft_strlcat(exp_str, env_value, exp_len + 1);
	ft_strlcat(exp_str, &str[*i], exp_len + 1);
	free(env_value);
	return (exp_str);
}

char	*get_env_value(char *str, size_t start, size_t i, char *envp[])
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
