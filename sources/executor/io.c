/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/06/27 21:52:08 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	 USE_READLINE
#include "minishell.h"

int	get_valid_fd(void) {
    int v_fd = -1;
    int retry_count = 0;
    const int max_retries = 10;  // 최대 반복 횟수 설정

    while (retry_count < max_retries) {
        v_fd = dup(0);
        if (v_fd != -1)
            break;
        else
            retry_count++;
    }
    if (v_fd == -1) {
        perror("Failed to duplicate file descriptor");
    }
    return (v_fd);
}

void	io_readline(int fd, const char *str)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		printf("> \033[s\b\b");
		line = readline("> ");
		if (!line)
		{
			printf("\033[u\033[1B\033[1A");
			break ;
		}
		if (ft_strlen(line) == ft_strlen(str) && \
		ft_strncmp(line, str, ft_strlen(line)) == 0)
			break ;
		// ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
}

// void	io_readline(int fd[3], const char *str)
// {
// 	char	*line;

// 	line = "none";
// 	while (line != 0)
// 	{
// 		printf("heredoc> \033[s\b\b\b\b\b\b\b\b\b");
// 		line = readline("heredoc> ");
// 		if (!line)
// 		{
// 			printf("\033[u\033[1B\033[1A");
// 			break ;
// 		}
// 		if (ft_strlen(line) == ft_strlen(str) && \
// 		ft_strncmp(line, str, ft_strlen(line)) == 0)
// 			break ;
// 		ft_putstr_fd(line, fd[2]);
// 		free(line);
// 	}
// 	free(line);
// }

void	print_fd(int fd)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		line = get_next_line(fd);
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
		//print_fd(fd);
	if (close(fd[2]) == -1)
		err_ctrl("close error ", 1, EXIT_FAILURE);
}

int	exec_io_here(t_ast_node *node)
{
	int				fd;
	struct termios	old_term;

	fd = get_valid_fd();
	set_echoctl(&old_term, ECHOCTL_OFF);
	if (dup2(fd, STDIN_FILENO) == -1)
		err_ctrl("dup2 error ", 1, EXIT_FAILURE);
	io_readline(fd, node->child[0]->token->str);
	print_fd(fd);
	// if (close(fd) == -1)
	// 	err_ctrl("close error", 1, EXIT_FAILURE);
	//heredoc_parents(fd);
	return (0);
}

// int	exec_io_here(t_ast_node *node)
// {
// 	pid_t			pid;
// 	int				fd[3];
// 	struct termios	old_term;

// 	pipe(fd);
// 	fd[2] = valid_fd();
// 	pid = fork();
// 	if (pid == -1)
// 		return (-1);
// 	if (pid == 0)
// 	{
// 		set_echoctl(&old_term, ECHOCTL_OFF);
// 		signal(SIGINT, SIG_DFL);
// 		if (dup2(fd[1], fd[2]) == -1)
// 			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
// 		io_readline(fd, node->child[0]->token->str);
// 		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
// 			err_ctrl("close error ", 1, EXIT_FAILURE);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 		heredoc_parents(fd);
// 	return (0);
// }

int	exec_io_file(t_ast_node *node)
{
	int	fd;

	if (node->token->type == LESS)
		fd = open(node->child[0]->token->str, O_RDONLY);
	else if (node->token->type == GREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token->type == DGREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		err_ctrl("file open error", 1, EXIT_FAILURE);
	if (node->token->type == LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			err_ctrl("dup2 error", 1, EXIT_FAILURE);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			err_ctrl("dup2 error", 1, EXIT_FAILURE);
	}
	if (close(fd) == -1)
		err_ctrl("file close error ", 1, EXIT_FAILURE);
	return (0);
}
