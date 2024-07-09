/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:46:20 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 20:46:31 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_sequence(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, COMMAND, NULL), err, 2))
		return (0);
	if (command(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, PIPE_SEQUENCE_, NULL), err, 2))
			return (0);
		if (pipe_sequence_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	pipe_sequence_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_PIPE)
	{
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(0, COMMAND, NULL), err, 2))
			return (0);
		if (command(toknode, curr->child[0], err))
		{
			if (add_ast_child(curr, \
			new_ast_node(1, PIPE_SEQUENCE_, NULL), err, 2))
				return (0);
			if (pipe_sequence_(toknode, curr->child[1], err))
				return (1);
		}
		if (curr_tokentype(toknode) == TOK_NEWLINE)
			err->errnum = INCOMPLETE_CMD;
		else
			err->token = curr_token(toknode);
		return (0);
	}
	return (1);
}
