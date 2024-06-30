/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:03:57 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/30 19:51:27 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_single_env_var(char *env_var, char ***envp);
size_t	get_key_len(char *env_var);
char	**search_env_var(const char *key, size_t len, char *envp[]);
int		export_new_env_var(char *new_env_var, char ***envp);

int	export(char **argv, char ***envp)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (is_assignment_word(argv[i]))
			if (export_single_env_var(argv[i], envp))
				return (-1);
		i++;
	}
	return (0);
}

int	export_single_env_var(char *env_var, char ***envp)
{
	char	**old_env_var;
	char	*new_env_var;

	new_env_var = ft_strdup(env_var);
	if (new_env_var == NULL)
		return (-1);
	old_env_var = search_env_var(env_var, get_key_len(env_var), *envp);
	if (old_env_var)
	{
		free(*old_env_var);
		*old_env_var = new_env_var;
	}
	else
		if (export_new_env_var(new_env_var, envp))
		{
			free(new_env_var);
			return (-1);
		}
	return (0);
}

size_t	get_key_len(char *env_var)
{
	const char	*equalsign_start;

	equalsign_start = ft_strchr(env_var, '=');
	return (equalsign_start - env_var);
}

char	**search_env_var(const char *key, size_t len, char *envp[])
{
	size_t	i;

	if (key == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

int	export_new_env_var(char *new_env_var, char ***envp)
{
	size_t	envp_len;
	char	**new_envp;

	envp_len = ft_strslen(*envp);
	new_envp = (char **)ft_calloc(envp_len + 2, sizeof(char *));
	if (new_envp == NULL)
		return (err_return("malloc"));
	ft_memcpy(new_envp, *envp, envp_len + 2);
	new_envp[envp_len] = new_env_var;
	ft_free_strs(*envp);
	*envp = new_envp;
	return (0);
}
