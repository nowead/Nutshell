/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/06/09 15:01:55 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_fd(void)
{
	int	 v_fd;

	v_fd = 0;
	while (1)
	{
		v_fd = dup(0);
		if (v_fd == -1)
			continue ;
		else
			break ;
	}
	return (v_fd);
}

void	io_readline(int fd[3])
{
	char	*line;

	while (line != 0)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line || (ft_strlen(line) - 1 == ft_strlen(av[2] && \
			ft_strncmp(line, av[2], ft_strlen(line) -1) == 0)))
				break;
			ft_printf("%s", line);
			free(line);
		}
		free(line);
}

int	io_here()
{
	pid_t	pid;
	int		fd[3];

	pipe(fd);
	fd[3] = valid_fd();
	pid = fork();
	if (pid == 1)
		err_ctrl("fork fail ", 1, EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if(close(fd[0]) == -1 || close(fd[1]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		io_readline(fd);
		exit(EXIT_SUCCESS);
	}
}

int	here_end()
{

}
