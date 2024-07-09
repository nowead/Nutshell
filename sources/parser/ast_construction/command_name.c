/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:59:52 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/09 21:00:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_name(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		if (is_assignment_word_token(curr_token(toknode)))
			curr_token(toknode)->type = TOK_ASSIGNMENT_WORD;
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}

int	cmd_word(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		if (is_assignment_word_token(curr_token(toknode)))
			curr_token(toknode)->type = TOK_ASSIGNMENT_WORD;
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}
