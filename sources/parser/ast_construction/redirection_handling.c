/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:36:25 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:10:14 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_list(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL), err, 2))
		return (0);
	if (io_redirect(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, REDIRECT_LIST, NULL), err, 2))
			return (0);
		return (redirect_list(toknode, curr->child[1], err));
	}
	clear_ast_tree(curr->child[0]);
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	io_redirect(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_FILE, NULL), err, 1))
		return (0);
	if (io_file(toknode, curr->child[0], err))
		return (1);
	if (is_ast_err(err))
		return (0);
	clear_ast_tree(curr->child[0]);
	if (add_ast_child(curr, new_ast_node(0, IO_HERE, NULL), err, 1))
		return (0);
	if (io_here(toknode, curr->child[0], err))
		return (1);
	clear_ast_tree(curr->child[0]);
	return (0);
}
