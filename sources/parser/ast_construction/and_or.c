/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:43:59 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:13:02 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	and_or(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL), err, 2))
		return (0);
	if (pipe_sequence(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, AND_OR_, NULL), err, 2))
			return (0);
		if (and_or_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	and_or_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_AND_IF || \
	curr_tokentype(toknode) == TOK_OR_IF)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		if (curr_tokentype(toknode) == TOK_NEWLINE)
		{
			err->errnum = INCOMPLETE_CMD;
			return (0);
		}
		if (add_ast_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL), err, 2))
			return (0);
		if (pipe_sequence(toknode, curr->child[0], err))
		{
			if (add_ast_child(curr, new_ast_node(1, AND_OR_, NULL), err, 2))
				return (0);
			if (and_or_(toknode, curr->child[1], err))
				return (1);
		}
		err->token = curr_token(toknode);
		return (0);
	}
	return (1);
}
