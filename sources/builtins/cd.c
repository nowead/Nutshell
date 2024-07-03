/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:29:22 by damin             #+#    #+#             */
/*   Updated: 2024/07/03 20:53:10 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char **argv, char ***envp)
{
	int		oldpwd_index;
	int		pwd_index;
	int		i;

	if (!argv[1])
		return (0);
	if (ft_strncmp(argv[1], "~", 1) == 0 && cd_home(argv, *envp) == -1)
		return (-1);
	i = -1;
	oldpwd_index = -1;
	pwd_index = -1;
	while ((*envp)[++i])
	{
		if (ft_strncmp((*envp)[i], "OLDPWD", 6) == 0)
			oldpwd_index = i;
		if (ft_strncmp((*envp)[i], "PWD", 3) == 0)
			pwd_index = i;
	}
	if (oldpwd_index != -1 && update_oldpwd(envp, oldpwd_index, pwd_index) == -1)
		return (-1);
	if (chdir(argv[1]) == -1)
        return (err_return("chdir"));
	if (pwd_index != -1 && update_pwd(envp, pwd_index) == -1)
		return (-1);
	return (0);
}

int	update_oldpwd(char ***envp, int oldpwd_index, int pwd_index)
{
	char	*tmp;

	tmp = (char *)ft_calloc(4, sizeof(char));
	if (tmp == NULL)
		return (err_return("malloc"));
	ft_strlcpy(tmp, "OLD", 4);
	(*envp)[oldpwd_index] = ft_strjoin(tmp, (*envp)[pwd_index]);
	free (tmp);
	return (0);
}

int	update_pwd(char ***envp, int pwd_index)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (err_return("getcwd"));
	tmp = (char *)ft_calloc(4, sizeof(char));
	if (tmp == NULL)
		return (err_return("malloc"));
	ft_strlcpy(tmp, "PWD=", 5);
	(*envp)[pwd_index] = ft_strjoin(tmp, cwd);
	free(tmp);
	free(cwd);
	if((*envp)[pwd_index] == NULL)
		return (err_return("malloc"));
	return (0);
}

int	cd_home(char **argv, char **envp)
{
	int		i;
	char	*tmp;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			tmp = (char *)ft_calloc(ft_strlen(&envp[i][5]) + 1, sizeof(char));
			if (tmp == NULL)
				return (err_return("malloc"));
			ft_strlcpy(tmp, &envp[i][5], ft_strlen(&envp[i][5]) + 1);
			argv[1] = tmp;
			break ;
		}
	}
	return (0);
}