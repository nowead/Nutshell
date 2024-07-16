/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:39:43 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 22:51:13 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_io_file(t_ast_node *node)
{
	int	fd;

	fd = -1;
	if (node->token->type == TOK_LESS)
		fd = open(node->child[0]->token->str, O_RDONLY);
	else if (node->token->type == TOK_GREAT)
		fd = open(node->child[0]->token->str, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token->type == TOK_DGREAT)
		fd = open(node->child[0]->token->str, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (err_return(-1, "file open"));
	if (node->token->type == TOK_LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (err_return(-1, "dup2"));
	}
	else if (dup2(fd, STDOUT_FILENO) == -1)
		return (err_return(-1, "dup2"));
	if (close(fd) == -1)
		return (err_return(-1, "close"));
	return (0);
}
