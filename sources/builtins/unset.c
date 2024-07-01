/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:53:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/01 23:00:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(char **argv, char ***envp)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_name(argv[i], ft_strlen(argv[i])))
			if (unset_single_env_var(argv[i], envp))
				return (-1);
		i++;
	}
	return (0);
}

int	unset_single_env_var(char *env_key, char ***envp)
{
	char	**env_var;
	char	**new_envp;
	size_t	envp_len;
	size_t	i;

	env_var = search_env_var(env_key, ft_strlen(env_key), *envp);
	if (env_var == NULL)
		return (1);
	envp_len = ft_strslen(*envp);
	new_envp = (char **)ft_calloc(envp_len, sizeof(char *));
	if (new_envp == NULL)
		return (-1);
	i = 0;
	while (i < envp_len - 1)
	{
		if ((*envp)[i] != *env_var)
			new_envp[i] = (*envp)[i];
		i++;
	}
	free(*envp);
	*envp = new_envp;
	return (0);
}
