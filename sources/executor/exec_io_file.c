/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:39:43 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/11 16:39:54 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_io_file(t_ast_node *node)
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
		err_exit("file open error", 1, EXIT_FAILURE);
	if (node->token->type == TOK_LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			err_exit("dup2 error", 1, EXIT_FAILURE);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			err_exit("dup2 error", 1, EXIT_FAILURE);
	}
	if (close(fd) == -1)
		err_exit("file close error ", 1, EXIT_FAILURE);
	return (0);
}
