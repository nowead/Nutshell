/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 22:53:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 14:36:49 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(char **argv, char ***envp)
{
	size_t	i;
	int		err_flag;

	err_flag = 0;
	i = 1;
	while (argv[i])
	{
		if (is_valid_name(argv[i], ft_strlen(argv[i])))
		{
			if (unset_single_env_var(argv[i], envp))
				return (0);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, \
			"`%s': not a valid identifier\n", argv[i]);
			err_flag = 1;
		}
		i++;
	}
	if (err_flag)
		return (1);
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
		else
		{
			new_envp[i] = (*envp)[i + 1];
			i++;
		}
		i++;
	}
	free(*env_var);
	free(*envp);
	*envp = new_envp;
	return (0);
}

void	exec_unset_in_process(char **argv, char ***envp)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_name(argv[i], ft_strlen(argv[i])))
		{
			if (unset_single_env_var(argv[i], envp))
				exit(EXIT_FAILURE);
		}
		else
			ft_dprintf(STDERR_FILENO, \
			"`%s': not a valid identifier\n", argv[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
