/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc_tempfile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:16:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/17 20:19:17 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_here_doc_tempfile(char **file_name, char *envp[])
{
	int		fd;
	char	*home_path;

	home_path = ft_strjoin(ft_getenv("HOME", envp), "/.here_doc_");
	if (home_path == NULL)
		return (err_return(-1, "ft_strjoin"));
	fd = create_unique_file(file_name, home_path);
	free(home_path);
	return (fd);
}

int	create_unique_file(char **file_name, char *home_path)
{
	size_t	i;
	int		fd;
	char	*num;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		*file_name = ft_strjoin(home_path, num);
		if (*file_name == NULL)
			return (err_return(-1, "ft_strjoin"));
		if (access(*file_name, F_OK) == -1)
		{
			free (num);
			fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (err_return(-1, "open"));
			break ;
		}
		free (num);
		free (*file_name);
		i++;
	}
	return (fd);
}
