/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/12 20:23:03 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int e_simple_cmd(t_ast_node *node)
{
	return (0);
}

int	first_cmd(t_ast_node *node)
{
	ft_printf("this is first_cmd\n");
	return (0);
}

int	middle_cmd(t_ast_node *node)
{
	ft_printf("this is middle_cmd\n");
	return (0);
}

int	last_cmd(t_ast_node *node, int depth)
{
	if (depth == 0) // 단일 명령어
		ft_printf("this is only one cmd\n");
	else
		ft_printf("this is last cmd\n");
	return (0);
}

int	e_cmd(t_ast_node *node, int depth)
{
	int			i;
	t_ast_node	*start_node;

	if (depth == 0)
		return (last_cmd(node, depth));
	i = 0;
	start_node = node;
	while (i < depth)
	{
		start_node = start_node->parent;
		++i;
	}
	first_cmd(start_node);
	start_node = start_node->child[0];
	while (i > 1)
	{
		middle_cmd(start_node);
		if (start_node->child)
			start_node = start_node->child[0];
		--i;
	}
	return (last_cmd(start_node, depth));
}

int e_pipe_sequence_(t_ast_node *node, int depth)
{
	int	ret_pipe_sequence_;

	ret_pipe_sequence_ = -1;
	if (node == NULL)
		return (-1);
	if (node->child)
		ret_pipe_sequence_ = e_pipe_sequence_(node->child[1], depth + 1);
	if (node->child && ret_pipe_sequence_ == -1)
		return (e_cmd(node->child[0], depth));
	return (ret_pipe_sequence_);
}

int e_pipe_sequence(t_ast_node *node)
{
	int	ret_pipe_sequence_;

	// if (node == NULL) //pipe_sequence 노드는 무조건 있어야함
	// 	return (-1);
	ret_pipe_sequence_ = -1;
	if (node->child)
		ret_pipe_sequence_ = e_pipe_sequence_(node->child[1], 1);
	if (node->child && ret_pipe_sequence_ == -1)
		return (e_cmd(node->child[0], 0));
	return (ret_pipe_sequence_);
}

int e_and_or_(t_ast_node *node, int ret_pipe_sequence)
{
	int	ret_new_pipe_sequence;

	if (node == NULL)
		return (ret_pipe_sequence);
	ret_new_pipe_sequence = 0;
	if (node->token && \
	((node->token->type == AND_IF && ret_pipe_sequence == 0) ||\
	 (node->token->type == OR_IF && ret_pipe_sequence == -1)))
	{
		if (node->child)
		{
			ret_new_pipe_sequence = e_pipe_sequence(node->child[0]);
			return (e_and_or_(node->child[1], ret_new_pipe_sequence));
		}
	}
	return (ret_pipe_sequence);
}

int	e_and_or(t_ast_node *node)
{
	int	ret_pipe_sequence;

	ret_pipe_sequence= -1;
	if (node->child)
	{
		ret_pipe_sequence = e_pipe_sequence(node->child[0]);
		return (e_and_or_(node->child[1], ret_pipe_sequence));
	}
	return (ret_pipe_sequence);
}
