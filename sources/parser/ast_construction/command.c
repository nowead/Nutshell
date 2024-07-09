/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:35:03 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 20:49:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, SIMPLE_COMMAND, NULL), err, 2))
		return (0);
	if (simple_command(toknode, curr->child[0], err))
		return (1);
	else if (!is_ast_err(err))
	{
		clear_ast_tree(curr->child[0]);
		if (add_ast_child(curr, new_ast_node(0, SUBSHELL, NULL), err, 2))
			return (0);
		if (subshell(toknode, curr->child[0], err))
		{
			if (add_ast_child(curr, \
			new_ast_node(1, REDIRECT_LIST, NULL), err, 2))
				return (0);
			if (redirect_list(toknode, curr->child[1], err))
				return (1);
		}
	}
	return (0);
}

int	simple_command(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, CMD_PREFIX, NULL), err, 3))
		return (0);
	if (cmd_prefix(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_TOK_WORD, NULL), err, 3))
			return (0);
		if (cmd_word(toknode, curr->child[1]))
		{
			if (add_ast_child(curr, new_ast_node(2, CMD_SUFFIX, NULL), err, 3))
				return (0);
			if (cmd_suffix(toknode, curr->child[2], err))
				return (1);
			err->token = curr_token(toknode);
			return (0);
		}
		clear_ast_tree(curr->child[1]);
		return (1);
	}
	else if (!is_ast_err(err))
		return (simple_command_(toknode, curr, err));
	return (0);
}

int	simple_command_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	clear_ast_tree(curr->child[0]);
	if (add_ast_child(curr, new_ast_node(0, CMD_NAME, NULL), err, 3))
		return (0);
	if (cmd_name(toknode, curr->child[0]))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL), err, 3))
			return (0);
		if (cmd_suffix(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	clear_ast_tree(curr->child[0]);
	return (0);
}
