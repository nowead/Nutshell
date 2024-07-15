/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/07/16 01:11:01 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx)
// {
// 	int				fd;
// 	char			*file_name;

// 	set_echoctl(NULL, ECHOCTL_OFF);
// 	fd = open_here_doc_tempfile_write(&file_name, shell_ctx->envp);
// 	io_readline(fd, node->child[0]->token->str, shell_ctx);
// 	if (close(fd) == -1)
// 		err_exit("close", 1, EXIT_FAILURE);
// 	fd = open(file_name, O_RDONLY, 0644);
// 	if (fd == -1)
// 		err_exit("open", 1, EXIT_FAILURE);
// 	shell_ctx->stdfd[0] = dup(STDIN_FILENO);
// 	if (shell_ctx->stdfd[0] == -1)
// 		err_exit("dup2 error", 1, EXIT_FAILURE);
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 		err_exit("dup2 error", 1, EXIT_FAILURE);
// 	if (unlink(file_name) == -1)
// 		err_exit("unlink", 1, EXIT_FAILURE);
// 	if (is_there_next_io_here(node))
// 		if (dup2(shell_ctx->stdfd[0], STDIN_FILENO) == -1)
// 			err_exit("dup2 error", 1, EXIT_FAILURE);
// 	if (close(fd) == -1 || close(shell_ctx->stdfd[0]) == -1)
// 		err_exit("close", 1, EXIT_FAILURE);
// 	free(file_name);
// 	return (0);
// }

int	exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx)
{
	int				fd;
	char			*file_name;
	int				backup_pipe_fd[2];

	set_echoctl(NULL, ECHOCTL_OFF);
	fd = open_here_doc_tempfile_write(&file_name, shell_ctx->envp);

// backup pipe fd
	backup_pipe_fd[0] = dup(STDIN_FILENO);
	backup_pipe_fd[1] = dup(STDOUT_FILENO);
	if (backup_pipe_fd[0] == -1 || backup_pipe_fd[1] == -1)
		err_exit("dup", 1, EXIT_FAILURE);

// restore original stdin, stdout
	if (dup2(shell_ctx->stdfd[0], STDIN_FILENO) == -1)
		err_exit("dup2", 1, EXIT_FAILURE);
	if (dup2(shell_ctx->stdfd[1], STDOUT_FILENO) == -1)
		err_exit("dup2", 1, EXIT_FAILURE);

	io_readline(fd, node->child[0]->token->str, shell_ctx);

// restore pipe fd
	if (dup2(backup_pipe_fd[0], STDIN_FILENO) == -1)
		err_exit("dup2", 1, EXIT_FAILURE);
	if (dup2(backup_pipe_fd[1], STDOUT_FILENO) == -1)
		err_exit("dup2", 1, EXIT_FAILURE);
	if (close(backup_pipe_fd[0]) == -1 || close(backup_pipe_fd[1]) == -1)
		err_exit("close", 1, EXIT_FAILURE);

// close opened fd
	if (close(fd) == -1)
		err_exit("close", 1, EXIT_FAILURE);
// // reopen file RDONLY
// 	fd = open(file_name, O_RDONLY, 0644);
// 	if (fd == -1)
// 		err_exit("open", 1, EXIT_FAILURE);

	// shell_ctx->stdfd[0] = dup(STDIN_FILENO);
	// if (shell_ctx->stdfd[0] == -1)
	// 	err_exit("dup2 error", 1, EXIT_FAILURE);

	// if (dup2(fd, STDIN_FILENO) == -1)
	// 	err_exit("dup2 error", 1, EXIT_FAILURE);
		
	// if (unlink(file_name) == -1)
	// 	err_exit("unlink", 1, EXIT_FAILURE);

	// if (is_there_next_io_here(node))
	// 	if (dup2(shell_ctx->stdfd[0], STDIN_FILENO) == -1)
	// 		err_exit("dup2 error", 1, EXIT_FAILURE);

	// if (close(fd) == -1 || close(shell_ctx->stdfd[0]) == -1)
	// 	err_exit("close", 1, EXIT_FAILURE);
	free(file_name);
	return (0);
}

int	is_there_next_io_here(t_ast_node *curr)
{
	curr = curr->parent->parent;
	if (curr->child && curr->child[1])
		curr = curr->child[1];
	else
		return (0);
	if (curr->child && curr->child[0])
		curr = curr->child[0];
	else
		return (0);
	if (curr->sym == IO_REDIRECT && curr->child[0]->sym == IO_HERE)
		return (1);
	return (0);
}

int	open_here_doc_tempfile_write(char **file_name, char *envp[])
{
	int			fd;

	*file_name = ft_strjoin(ft_getenv("HOME", envp), "/.here_doc");
	if (*file_name == NULL)
		return (err_return(1, "ft_strjoin"));
	fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (err_return(1, "open"));
	return (fd);
}

void	io_readline(int fd, const char *delimiter, t_shell_ctx *shell_ctx)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		printf("> \033[s\b\b");
		line = readline("> ");
		if (!line)
		{
			ft_printf("\033[u\033[1B\033[1A");
			break ;
		}
		if (expand_parameters_in_string(&line, shell_ctx) == -1)
			err_exit("expand_parameters_in_string", 1, EXIT_FAILURE);
		if (ft_strlen(line) == ft_strlen(delimiter) && \
		ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(line);
}
