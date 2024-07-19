/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:39:43 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/19 13:36:37 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_io_file(t_ast_node *node)
{
	int	fd;

	fd = exec_io_file_redirect(node);
	if (fd == -1)
	{
		ft_dprintf(2, "Nutshell: %s: No such file or directory\n", \
		node->child[0]->token->str);
		return (-1);
	}
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

int	exec_io_file_redirect(t_ast_node *node)
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
	return (fd);
}
