/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:49:18 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:13:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	subshell(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_LPAREN)
	{
		set_next_token(toknode);
		if (curr_tokentype(toknode) == TOK_NEWLINE)
		{
			err->errnum = INCOMPLETE_CMD;
			return (0);
		}
		if (add_ast_child(curr, new_ast_node(0, AND_OR, NULL), err, 1))
			return (0);
		if (and_or(toknode, curr->child[0], err))
		{
			if (curr_tokentype(toknode) == TOK_RPAREN)
			{
				set_next_token(toknode);
				return (1);
			}
		}
		err->token = curr_token(toknode);
	}
	return (0);
}
