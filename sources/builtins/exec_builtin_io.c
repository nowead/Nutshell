/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:45:56 by damin             #+#    #+#             */
/*   Updated: 2024/07/12 16:19:05 by seonseo          ###   ########.fr       */
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
		return (err_return(1, "builtin open tempfile"));
	io_readline(fd, node->child[0]->token->str);
	if (close(fd) == -1)
		return (err_return(1, "close"));
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (err_return(1, "open"));
	if (dup2(STDIN_FILENO, stdin_fd) == -1)
		return (err_return(1, "dup2 error"));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (err_return(1, "dup2 error"));
	if (unlink(file_name) == -1)
		return (err_return(1, "unlink"));
	if (close(fd) == -1 || close(STDIN_FILENO) == -1)
		return (err_return(1, "close"));
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		return (err_return(1, "dup2 error"));
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
		return (err_return(1, "open"));
	if (node->token->type == TOK_LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (err_return(1, "dup2"));
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (err_return(1, "dup2"));
	}
	if (close(fd) == -1)
		return (err_return(1, "close"));
	return (0);
}
