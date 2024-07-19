/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:04:14 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/19 15:46:47 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	exec_absolute_path(const char *file, char *const argv[], \
char *envp[]);
static char	*ft_execvpe_search(const char *file, char *dirs[]);
static char	*path_join(const char *dir, const char *file);

int	ft_execvpe(const char *file, char *const argv[], char *envp[])
{
	char	**dirs;
	char	*path;

	if (file == NULL || *file == '\0')
	{
		errno = ENOENT;
		return (-1);
	}
	if (ft_strchr(file, '/'))
	{
		if (exec_absolute_path(file, argv, envp) == -1)
			return (-1);
		return (0);
	}
	dirs = ft_split(ft_getenv("PATH", envp), ':');
	if (dirs == NULL)
		return (-1);
	path = ft_execvpe_search(file, dirs);
	ft_free_strs(dirs);
	if (path != NULL)
		execve(path, argv, envp);
	return (-1);
}

static int	exec_absolute_path(const char *file, char *const argv[], \
char *envp[])
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == -1)
		return (-1);
	if (S_ISDIR(file_stat.st_mode))
	{
		errno = EISDIR;
		return (-1);
	}
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == 0)
			return (execve(file, argv, envp));
		else
			return (-1);
	}
	errno = EFAULT;
	return (-1);
}

static char	*ft_execvpe_search(const char *file, char *dirs[])
{
	int		i;
	char	*path;

	i = 0;
	while (dirs[i])
	{
		path = path_join(dirs[i], file);
		if (path == NULL)
			break ;
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				return (path);
			else
			{
				free(path);
				ft_dprintf(2, "Nutshell: %s: Permission denied\n", path);
				break ;
			}
		}
		free(path);
		i++;
	}
	return (NULL);
}

static char	*path_join(const char *dir, const char *file)
{
	size_t	dir_len;
	size_t	file_len;
	size_t	full_path_len;
	char	*full_path;

	dir_len = ft_strlen(dir);
	file_len = ft_strlen(file);
	full_path_len = dir_len + file_len + 2;
	full_path = (char *)malloc(sizeof(char) * full_path_len);
	if (full_path == NULL)
		return (NULL);
	ft_strlcpy(full_path, dir, full_path_len);
	if (dir[dir_len - 1] != '/')
		ft_strlcat(full_path, "/", full_path_len);
	ft_strlcat(full_path, file, full_path_len);
	return (full_path);
}
