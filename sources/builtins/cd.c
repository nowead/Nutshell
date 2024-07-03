/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:29:22 by damin             #+#    #+#             */
/*   Updated: 2024/07/03 22:53:36 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char **argv, char ***envp)
{
	char	**oldpwd;
	char	**pwd;

	if (!argv[1])
		return (0);
	if (ft_strncmp(argv[1], "~", 1) == 0 && cd_home(argv, *envp) == -1)
		return (-1);
	if (update_oldpwd(envp) == -1)
		return (-1);
	if (chdir(argv[1]) == -1)
        return (err_return("chdir"));
	if (update_pwd(envp) == -1)
		return (-1);
	return (0);
}

int	update_oldpwd(char ***envp)
{
	char	**old_pwd;

	old_pwd = search_env_var("OLDPWD", 6, *envp);
	// free(*old_pwd);
	*old_pwd = ft_strjoin("OLD", *(search_env_var("PWD", 3, *envp)));
	if (*old_pwd == NULL)
		return (err_return("ft_strjoin"));
	return (0);
}

int	update_pwd(char ***envp)
{
	char	*cwd;
	char	**pwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (err_return("getcwd"));
	pwd = search_env_var("PWD", 3, *envp);
	// free(*pwd);
	*pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (*pwd == NULL)
		return (err_return("ft_strjoin"));
	return (0);
}

int	cd_home(char **argv, char **envp)
{
	char	*env_home;

	env_home = ft_getenv("HOME", envp);
	free(argv[1]);
	argv[1] = ft_strjoin(env_home, &argv[1][1]);
	return (0);
}
