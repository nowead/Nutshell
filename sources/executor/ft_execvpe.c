/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:04:14 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/14 18:06:18 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (execve(file, argv, envp));
	dirs = ft_split(ft_getenv("PATH", envp), ':');
	if (dirs == NULL)
		return (-1);
	path = ft_execvpe_search(file, dirs);
	ft_free_strs(dirs);
	if (path != NULL)
		execve(path, argv, envp);
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
