/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:39:43 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/04 02:55:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sym : IO_FILE
int	exec_io_file(t_ast_node *node, t_shell_ctx *shell_ctx)
{
	int	fd;

	if (expand_io_filename(node->child[0], shell_ctx))
		return (-1);
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

int	expand_io_filename(t_ast_node *node, t_shell_ctx *shell_ctx)
{
	t_tokenlist	*expanded_token;

	expanded_token = expand_parameters_in_a_token(node->token, shell_ctx);
	if (expanded_token->size != 1)
	{
		clear_tokenlist(expanded_token);
		dprintf(2, "Nutshell: %s: ambiguous redirect\n", node->token->str);
		return (-1);
	}
	free(node->token->str);
	node->token->str = expanded_token->head->token->str;
	free(expanded_token->head->token);
	expanded_token->head->token = NULL;
	free(expanded_token->head);
	expanded_token->head = NULL;
	free(expanded_token);
	expanded_token = NULL;
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
