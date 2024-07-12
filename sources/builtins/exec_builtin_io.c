/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:45:56 by damin             #+#    #+#             */
/*   Updated: 2024/07/12 16:08:04 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_io_here(t_ast_node *node, char *envp[])
{
	int				fd;
	char			*file_name;
	int				stdin_fd;

	set_echoctl(NULL, ECHOCTL_OFF);
	fd = open_here_doc_tempfile(&file_name, envp);
	if (fd == -1)
		return (err_return(1, "builtin open tempfile: %s\n", strerror(errno)));
	io_readline(fd, node->child[0]->token->str);
	if (close(fd) == -1)
		return (err_return(1, "close: %s\n", strerror(errno)));
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (err_return(1, "open: %s\n", strerror(errno)));
	if (dup2(STDIN_FILENO, stdin_fd) == -1)
		return (err_return(1, "dup2 error: %s\n", strerror(errno)));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (err_return(1, "dup2 error: %s\n", strerror(errno)));
	if (unlink(file_name) == -1)
		return (err_return(1, "unlink: %s\n", strerror(errno)));
	if (close(fd) == -1 || close(STDIN_FILENO) == -1)
		return (err_return(1, "close: %s\n", strerror(errno)));
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		return (err_return(1, "dup2 error: %s\n", strerror(errno)));
	free(file_name);
	return (0);
}

int	exec_builtin_io_file(t_ast_node *node)
{
	int	fd;

	if (node->token->type == TOK_LESS)
		fd = open(node->child[0]->token->str, O_RDONLY);
	else if (node->token->type == TOK_GREAT)
		fd = open(node->child[0]->token->str, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token->type == TOK_DGREAT)
		fd = open(node->child[0]->token->str, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (err_return(1, "open: %s\n", strerror(errno)));
	if (node->token->type == TOK_LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (err_return(1, "dup2: %s\n", strerror(errno)));
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (err_return(1, "dup2: %s\n", strerror(errno)));
	}
	if (close(fd) == -1)
		return (err_return(1, "close: %s\n", strerror(errno)));
	return (0);
}
