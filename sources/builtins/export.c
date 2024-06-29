/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:03:57 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/29 21:17:23 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_single_key(char *env_var, char ***envp);
size_t	get_key_len(char *env_var);
char	**search_env_var(const char *key, size_t len, char *envp[]);

int	export(char **argv, char ***envp)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (is_assignment_word(argv[i]))
			if (export_single_key(argv[i], envp))
				return (-1);
		i++;
	}
	return (0);
}

int	export_single_key(char *env_var, char ***envp)
{
	char	*old_env_var

	if (search_env(env_var, get_key_len(env_var), *envp))
		update_env_var()
	
	return (0);
}

size_t	get_key_len(char *env_var)
{
	const char	*equalsign_start;

	equalsign_start = ft_strchr(token->str, '=');
	return ()
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

int	update_env_var()
{

}

int	export_new_env_var()
{
	size_t	envp_len;
	char	**new_envp;

	envp_len = ft_strslen(*envp);
	new_envp = (char **)ft_calloc(envp_len + 2, sizeof(char *));
	if (new_envp == NULL)
		return (err_return("malloc"));
	ft_memcpy(new_envp, *envp, envp_len + 2);
	ft_memcpy(new_envp + envp_len, curr->token->str, envp_len + 2);
	free(*envp);
	*envp = new_envp;
}
