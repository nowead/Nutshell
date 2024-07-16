/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:45:56 by damin             #+#    #+#             */
/*   Updated: 2024/07/16 15:58:00 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin_io_here(t_ast_node *node, t_shell_ctx *shell_ctx)
{
// 	int				fd;
// 	int				backup_pipe_fd[2];

// 	set_echoctl(NULL, ECHOCTL_OFF);
// 	fd = open_here_doc_tempfile_write(shell_ctx->envp);

// 	io_readline(fd, node->child[0]->token->str, shell_ctx);

// // close opened fd
// 	if (close(fd) == -1)
// 		err_exit("close", 1, EXIT_FAILURE);
// // reopen file RDONLY
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
}

void	exec_builtin_io_file(t_ast_node *node)
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
		err_exit("open", 1, 1);
	if (node->token->type == TOK_LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			err_exit("dup2", 1, 1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			err_exit("dup2", 1, 1);
	}
	if (close(fd) == -1)
		err_exit("close", 1, 1);
}
