/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:29:22 by damin             #+#    #+#             */
/*   Updated: 2024/07/08 16:28:04 by seonseo          ###   ########.fr       */
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
	if (update_pwd(envp) == -1)
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
	char	*new_old_pwd;
	char	*pwd;

	pwd = *(search_env_var("PWD", 3, *envp));
	if (pwd == NULL)
		return (-1);
	new_old_pwd = ft_strjoin("OLD", pwd);
	if (new_old_pwd == NULL)
		return (err_return("ft_strjoin"));
	if (export_single_env_var(new_old_pwd, envp) == -1)
	{
		free(new_old_pwd);
		return (err_return("export_single_env_var"));
	}
	free(new_old_pwd);
	return (0);
}

int	update_pwd(char ***envp)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (err_return("getcwd"));
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (pwd == NULL)
		return (err_return("ft_strjoin"));
	if (export_single_env_var(pwd, envp) == -1)
	{
		free(pwd);
		return (-1);
	}
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
