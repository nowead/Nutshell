/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/06/10 22:06:51 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_READLINE
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

	line = "none";
	while (line != 0)
	{
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		// printf("whenEOFisinput:[%s]\n", line);
		if (!line)
		{
			printf("\n");
			break;
		}
		if ((ft_strlen(line) - 1 == ft_strlen(str) && \
		ft_strncmp(line, str, ft_strlen(line) -1) == 0))
			break;
		ft_putstr_fd(line, fd[2]);
		free(line);
	}
	free(line);
}

void	print_fd(int fd[3])
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		line = get_next_line(fd[2]);
		if (line)
			ft_printf("%s", line);
	}
	//ft_printf("%s", fd[2]);
}

void	e_io_here(char *token_str)
{
	pid_t	pid;
	pid_t	c_pid;
	int		fd[3];
	int		status;

	pipe(fd);
	fd[2] = valid_fd();
	pid = fork();
	// 다음 Nutshell 프롬프트를 잠시 중지 시키고 자식에서 readline 해야함
	if (pid == -1)
		err_ctrl("fork fail ", 1, EXIT_FAILURE);
	if (pid == 0)
	{
		set_signal(pid);
		if (dup2(fd[2], fd[1]) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		io_readline(fd, token_str);
		if(close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (dup2(fd[0], fd[2]) == -1)
				err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		//print_fd(fd);
		if(close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
				err_ctrl("close error ", 1, EXIT_FAILURE);
		while (1)
		{
			c_pid = wait(&status);
			if (c_pid != -1) // pid 종료전 까지 무한루프
				break ;
		}
	}
}
