/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_components.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:35:52 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 20:59:51 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_prefix(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL), err, 2))
		return (0);
	if (io_redirect(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL), err, 2))
			return (0);
		if (cmd_prefix_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	else if (!is_ast_err(err) && is_assignment_word_token(curr_token(toknode)))
	{
		curr_token(toknode)->type = TOK_ASSIGNMENT_WORD;
		clear_ast_tree(curr->child[0]);
		if (add_ast_child(curr, \
		new_ast_node(0, TERMINAL, curr_token(toknode)), err, 2))
			return (0);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL), err, 2))
			return (0);
		if (cmd_prefix_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	cmd_prefix_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (cmd_prefix(toknode, curr, err))
		return (1);
	if (is_ast_err(err))
		return (0);
	clear_ast_tree(curr->child[0]);
	return (1);
}

int	cmd_suffix(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		if (add_ast_child(curr, \
		new_ast_node(0, TERMINAL, curr_token(toknode)), err, 2))
			return (0);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL), err, 2))
			return (0);
		if (cmd_suffix(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	else
		return (cmd_suffix_(toknode, curr, err));
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	cmd_suffix_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL), err, 2))
		return (0);
	if (io_redirect(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL), err, 2))
			return (0);
		if (cmd_suffix(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	clear_ast_tree(curr->child[0]);
	if (is_ast_err(err))
		return (0);
	return (1);
}
