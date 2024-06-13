/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/13 19:58:39 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	e_assignment_word(t_ast_node *node)
{
	return (0);
}

int	e_redirect_list(t_ast_node *node)
{
	return (0);
}

int	e_io_redirect(t_ast_node *node)
{
	return (0);
	//return (-1);
}

int	e_cmd_suffix(t_ast_node *node, char *option)
{
	if (node == NULL)
		return (0);
	if (node->child)
	{
		if (node->child[0]->sym == IO_REDIRECT)
			return (e_io_redirect(node->child[0]));
		else
		{
			//option ㅇㅔ node->token->str 이어붙임
			return (e_cmd_name(node->child[0], option));
		}
	}
	return (0);
}

int	e_cmd_name(t_ast_node *node, char *option)
{
	return (-1);
}

int	e_cmd_prefix_(t_ast_node *node)
{
	if (node->child)
	{
		if (node->child[0]->sym == IO_REDIRECT)
		{
			if (e_io_redirect(node->child[0]) == -1)
				return (-1);
		}
		else
			e_assignment_word(node->child[0]);
		return (e_cmd_prefix_(node->child[1]));
	}
	return (0);
}

int	e_cmd_prefix(t_ast_node *node)
{
	if (node->child[0]->sym == IO_REDIRECT)
	{
		if (e_io_redirect(node->child[0]) == -1)
			return (-1);
	}
	else
		e_assignment_word(node->child[0]);
	return (e_cmd_prefix_(node->child[1]));
}

int e_simple_cmd(t_ast_node *node)
{
	char	*option;

	if (node->child_num == 1)
		return (e_cmd_prefix(node->child[0]));
	else if (node->child_num == 2)
	{
		if (e_cmd_suffix(node->child[1], option) == -1)
			return (-1);
		return (e_cmd_name(node->child[0], option));
	}
	else
	{
		if (e_cmd_prefix(node->child[0]) == -1)
			return (-1);
		if (e_cmd_suffix(node->child[2], option) == -1)
			return (-1);
		return (e_cmd_name(node->child[1], option));
	}
	return (-1);
}

int	e_subshell(t_ast_node *node)
{
	return (0);
}

int	first_cmd(t_ast_node *node)
{
	ft_printf("this is first_cmd\n");
	if (node->child)
	{
		if (node->child_num == 1)
			return (e_simple_cmd(node->child[0]));
		else
		{
 			e_redirect_list(node->child[1]);
			return (e_subshell(node->child[0]));
		}
	}
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

int	e_pipe_sequence(t_ast_node *node)
{
	t_ast_node	*curr;

	curr = node;
	if (curr->child[1]->child == NULL || curr->child[1]->child[0] == NULL)
		return (last_cmd(curr, 0)); 
	if (first_cmd(curr->child[0]) == -1)
		return (-1);
	curr = curr->child[1];
	while (curr->child[1]->child && curr->child[1]->child[0])
	{
		if (middle_cmd(curr->child[0]) == -1)
			return (-1);
		curr = curr->child[1];
	}
	return (last_cmd(curr, 1));
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
