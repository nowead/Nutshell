/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:09:44 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:09:54 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_file(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_LESS || \
	curr_tokentype(toknode) == TOK_GREAT || \
	curr_tokentype(toknode) == TOK_DGREAT)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(0, FILENAME, NULL), err, 1))
			return (0);
		if (filename(toknode, curr->child[0]))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	filename(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}
