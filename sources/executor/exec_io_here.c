/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/07/19 13:22:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sym : here_end
int	exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx)
{
	int		fd;
	char	*file_name;
	int		ret;

	ret = 0;
	file_name = shell_ctx->heredoc_files[(shell_ctx->heredoc_idx)++];
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		ret = err_return(-1, "open");
	if (ret != -1)
		ret = here_doc_redirect_stdin(fd, file_name);
	if (ret == -1)
		return (-1);
	return (0);
}

int	here_doc_redirect_stdin(int fd, char *file_name)
{
	int	ret;

	ret = 0;
	if (dup2(fd, STDIN_FILENO))
			ret = err_return(-1, "dup2");
	if (close(fd) == -1)
		ret = err_return(-1, "close");
	return (ret);
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
