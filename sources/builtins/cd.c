/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:29:22 by damin             #+#    #+#             */
/*   Updated: 2024/07/18 11:55:20 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char **argv, char ***envp)
{
	if (!argv[1])
	{
		if (chdir(ft_getenv("HOME", *envp)) == -1)
			return (err_return(1, "chdir"));
		return (0);
	}
	if (argv[1] && ft_strncmp(argv[1], "~", 1) == 0 \
	&& cd_home(argv, *envp) == -1)
		return (-1);
	if (update_pwd(envp) == -1)
		return (-1);
	if (update_oldpwd(envp) == -1)
		return (-1);
	if (chdir(argv[1]) == -1)
	{
		ft_dprintf(STDERR_FILENO, \
		"Nutshell: cd: %s: No such file or directory\n", argv[1]);
		return (-1);
	}
	if (update_pwd(envp) == -1)
		return (-1);
	return (0);
}

int	update_oldpwd(char ***envp)
{
	char	*new_old_pwd;
	char	*pwd;

	pwd = *(search_env_var("PWD", 3, *envp));
	if (pwd == NULL)
		return (-1);
	new_old_pwd = ft_strjoin("OLD", pwd);
	if (new_old_pwd == NULL)
		return (err_return(1, "ft_strjoin"));
	if (export_single_env_var(new_old_pwd, envp) == -1)
	{
		free(new_old_pwd);
		return (err_return(1, "export_single_env_var"));
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
		return (err_return(1, "getcwd"));
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (pwd == NULL)
		return (err_return(1, "ft_strjoin"));
	if (export_single_env_var(pwd, envp) == -1)
	{
		free(pwd);
		return (-1);
	}
	free(pwd);
	return (0);
}

int	cd_home(char **argv, char **envp)
{
	char	*env_home;

	env_home = ft_getenv("HOME", envp);
	if (argv[1])
	{
		free(argv[1]);
		argv[1] = ft_strjoin(env_home, &argv[1][1]);
		if (argv[1] == NULL)
			return (-1);
	}
	return (0);
}

void	exec_cd_in_process(char **argv, char ***envp)
{
	if (!argv[1])
	{
		if (chdir(ft_getenv("HOME", *envp)) == -1)
			err_exit("chdir", 1, 1);
		exit(EXIT_SUCCESS);
	}
	if (argv[1] && ft_strncmp(argv[1], "~", 1) == 0 \
	&& cd_home(argv, *envp) == -1)
		err_exit("cd_home", 1, 1);
	if (chdir(argv[1]) == -1)
	{
		ft_dprintf(STDERR_FILENO, \
		"Nutshell: cd: %s: No such file or directory\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
