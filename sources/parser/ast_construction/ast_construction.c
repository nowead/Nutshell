/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:56:21 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 20:56:45 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*program(t_tokenlist *tokenlist, t_ast_err *err)
{
	t_toknode	*toknode;
	t_ast		*ast;
	t_ast_node	*root;

	if (tokenlist == NULL)
		return (NULL);
	toknode = tokenlist->head;
	root = new_ast_node(0, AND_OR, NULL);
	if (root == NULL)
		return (NULL);
	if (and_or(&toknode, root, err) && \
	curr_tokentype(&toknode) == TOK_NEWLINE)
	{
		ast = (t_ast *)malloc(sizeof(t_ast));
		if (ast == NULL)
			return (NULL);
		ast->root = root;
		ast->tokenlist = tokenlist;
		return (ast);
	}
	if (!is_ast_err(err) && \
	curr_tokentype(&toknode) != TOK_NEWLINE)
		err->token = curr_token(&toknode);
	clear_ast_tree(root);
	return (NULL);
}
