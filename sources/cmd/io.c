/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/06/23 20:43:24 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	 USE_READLINE
#include "minishell.h"

int	valid_fd(void)
{
	int	v_fd;

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
		// ft_printf("heredoc> ");
		// line = get_next_line(STDIN_FILENO);
		printf("heredoc> \033[s\b\b\b\b\b\b\b\b\b");
		line = readline("heredoc> ");
		if (!line)
		{
			printf("\033[u\033[1B\033[1A");
			break ;
		}
		if (ft_strlen(line) == ft_strlen(str) && \
		ft_strncmp(line, str, ft_strlen(line)) == 0)
			break ;
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
}

void	heredoc_parents(int fd[3])
{
	pid_t	c_pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	if (dup2(fd[0], fd[2]) == -1)
		err_ctrl("dup2 error ", 1, EXIT_FAILURE);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		err_ctrl("close error ", 1, EXIT_FAILURE);
	while (1)
	{
		c_pid = wait(&status);
		if (c_pid != -1)
			break ;
	}
	// if (WEXITSTATUS(status) != 130)
	// 	print_fd(fd);
	if (close(fd[2]) == -1)
		err_ctrl("close error ", 1, EXIT_FAILURE);
}

int	exec_io_here(t_ast_node *node)
{
	pid_t	pid;
	int		fd[3];

	pipe(fd);
	fd[2] = valid_fd();
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_signal(SIGINT_CHILD_HANDLER);
		if (dup2(fd[1], fd[2]) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		io_readline(fd, node->child[0]->token->str);
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
		heredoc_parents(fd);
	return (0);
}

int	exec_io_file(t_ast_node *node)
{
	int	fd;

	if (node->token->type == LESS)
		fd = open(node->child[0]->token->str, O_RDONLY);
	else if (node->token->type == GREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_TRUNC);
	else if (node->token->type == DGREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
		err_ctrl("file open error", 1, EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		err_ctrl("dup2 error", 1, EXIT_FAILURE);
	if (close(fd) == -1)
		err_ctrl("file close error ", 1, EXIT_FAILURE);
	return (0);
}
