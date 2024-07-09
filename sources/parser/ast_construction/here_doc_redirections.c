/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:10:15 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:10:28 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	io_here(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_DLESS)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(0, HERE_END, NULL), err, 1))
			return (0);
		if (here_end(toknode, curr->child[0]))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	here_end(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}
