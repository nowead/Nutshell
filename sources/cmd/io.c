/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/06/09 21:45:58 by damin            ###   ########.fr       */
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

void	io_readline(int fd[3], const char *str)
{
	char	*line;

	while (line != 0)
		{
			line = get_next_line(STDIN_FILENO);
			if (!line || (ft_strlen(line) - 1 == ft_strlen(str) && \
			ft_strncmp(line, str, ft_strlen(line) -1) == 0))
				break;
			ft_printf("%s", line);
			free(line);
		}
		free(line);
}

void	e_io_here(char *token_str)
{
	pid_t	pid;
	int		fd[3];

	pipe(fd);
	fd[2] = valid_fd();
	pid = fork();
	ft_printf("\n\nalskdjfalksjdf\n\n");
	// 다음 Nutshell 프롬프트를 잠시 중지 시키고 자식에서 readline 해야함
	if (pid == 1)
		err_ctrl("fork fail ", 1, EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if(close(fd[0]) == -1 || close(fd[1]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		ft_printf("asdfasfd\n");
		io_readline(fd, token_str);
		exit(EXIT_SUCCESS);
	}
}
