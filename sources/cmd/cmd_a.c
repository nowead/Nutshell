/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/11 21:25:18 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int simple_cmd()
{
	
}

int e_pipe_sequence_()
{
	e_cmd();
	e_pipe_sequence_();
}

int e_pipe_sequence(t_ast_node *node)
{
	int	i;

	if (node == NULL)
		return (1);
	i = 0;
	if (node->child && node->child_num == 2)
		return (e_pipe_sequence_(node->child[i]));
	return (e_cmd(node->child[i++]));
}

int e_and_or_(t_ast_node *node, int ret_pipe_sequence)
{
	int	i;
	int	ret_pipe_sequence_;

	if (node == NULL)
		return (1);
	ret_pipe_sequence_ = 0;
	i = 0;
	if ((node->token->type == AND_IF && ret_pipe_sequence == 1) ||\
	 (node->token->type == OR_IF && ret_pipe_sequence == 0))
	{
		if (node->child && i < node->child_num)
			ret_pipe_sequence_ = e_pipe_sequence(node->child[i++]);
		if (node->child && i < node->child_num)
			reaturn (e_and_or_(node->child[i], ret_pipe_sequence_));
	}
	return (1);
}

int	e_and_or(t_ast_node *node)
{
	int	i;
	int	ret_pipe_sequence;

	if (node == NULL)
		return (1);
	ret_pipe_sequence = 0;
	i = 0;
	if (node->child && i < node->child_num)
		ret_pipe_sequence = e_pipe_sequence(node->child[i++]);
	if (ret_pipe_sequence != 0 && i < node->child_num)
		return (e_and_or_(node->child[i], ret_pipe_sequence));
	return (ret_pipe_sequence);
}

	// simple_command   : cmd_prefix cmd_word cmd_suffix
	//              | cmd_prefix
	//              | cmd_name cmd_suffix
	//              ;
