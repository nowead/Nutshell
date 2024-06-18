/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/18 11:47:20 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	old_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return malloc(new_size);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	old_size = ft_strlen(ptr);
	if (new_size < old_size)
		old_size = new_size;
    ft_memcpy(new_ptr, ptr, old_size);
    free(ptr);
	return (new_ptr);
}

int	e_assignment_word(t_ast_node *node)
{
	return (0);
}

int	e_redirect_list(t_ast_node *node)
{
	if (node->sym == IO_FILE)
		return (e_io_file(node));
	else if (node->sym == IO_HERE)
		return (e_io_here(node->child[0]));
	return (0);
}

int	e_io_redirect(t_ast_node *node)
{
	if (node->child[0]->sym == IO_FILE)
		return (e_io_file(node->child[0]));
	else if (node->child[0]->sym == IO_HERE)
		return (e_io_here(node->child[0]));
	return (0);
	//return (-1);
}

int	e_cmd_suffix(t_ast_node *node, char **option)
{
	size_t	dst_size;

	if (node != NULL && node->child)
	{
		if (node->child[0] && node->child[0]->sym == IO_REDIRECT)
		{
			if (e_io_redirect(node->child[0]) == -1)
				return (-1);
			if (e_cmd_suffix(node->child[1], option) == -1)
				return (-1);
		}
		else if (node->child[0] && node->child[0]->sym == TERMINAL)
		{
			dst_size = ft_strlen(*option) + ft_strlen(node->child[0]->token->str) + 2;
			*option = (char *)ft_realloc(*option, dst_size);
			if (*option == NULL)
				return (-1);
			ft_strlcat(*option, " ", ft_strlen(*option) + 2);
			ft_strlcat(*option, node->child[0]->token->str, dst_size);
			if (e_cmd_suffix(node->child[1], option) == -1)
				return (-1);
		}
	}
	return (0);
}

int	e_cmd_name(t_ast_node *node, char **option)
{
	char	**options;

	printf("[cmd_name:%s] : [cmd_options:%s]\n", node->token->str, *option);
	options = ft_split(*option, ' ');
	if (options == NULL)
		return (-1);
	return (0);
}

int	e_cmd_prefix_(t_ast_node *node)
{
	int	ret;

	ret  = -1;
	if (node == NULL)
		return (0);
	if (node->child)
	{
		if (node->child[0] && node->child[0]->sym == IO_REDIRECT)
			ret = e_io_redirect(node->child[0]);
		else if (node->child[0] && node->child[0]->sym == ASSIGNMENT_WORD)
			ret = e_assignment_word(node->child[0]);
		if (node->child[1] && ret != -1)
			return (e_cmd_prefix_(node->child[1]));
	}
	return (0);
}

int	e_cmd_prefix(t_ast_node *node)
{
	int	ret;

	ret = -1;
	if (node->child[0] && node->child[0]->sym == IO_REDIRECT)
		ret = e_io_redirect(node->child[0]);
	else if (node->child[0] && node->child[0]->sym == ASSIGNMENT_WORD)
		ret = e_assignment_word(node->child[0]);
	if (node->child[1] && ret != -1)
		return (e_cmd_prefix_(node->child[1]));
	return (ret);
}

int e_simple_cmd(t_ast_node *node)
{
	char	**option;
	int		ret;

	ret = -1;
	option = (char **)malloc(sizeof(char *));
	if (option == NULL)
		return (-1);
	*option = (char *)calloc(1, sizeof(char));
	if (*option == NULL)
		return (-1);
	if (option == NULL)
		return (-1);
	if (node->child[0]->sym == CMD_PREFIX && node->child[1] == NULL)
		ret = e_cmd_prefix(node->child[0]);
	else if(node->child[0]->sym == CMD_NAME)
	{
		if (e_cmd_suffix(node->child[1], option) != -1)
			ret = (e_cmd_name(node->child[0], option));
	}
	else
	{
		if (e_cmd_prefix(node->child[0]) == -1)
			ret = -1;
		if (e_cmd_suffix(node->child[2], option) != -1)
			ret = e_cmd_name(node->child[1], option);
	}
	free(*option);
	free(option);
	return (ret);
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
		if (node->child[0] && node->child[0]->sym == SIMPLE_COMMAND)
			return (e_simple_cmd(node->child[0]));
		else
 			if (e_redirect_list(node->child[1]) != -1)
				return (e_subshell(node->child[0]));
	}
	return (-1);
}

int	middle_cmd(t_ast_node *node)
{
	ft_printf("this is middle_cmd\n");
	if (node->child)
	{
		if (node->child[0] && node->child[0]->sym == SIMPLE_COMMAND)
			return (e_simple_cmd(node->child[0]));
		else
 			if (e_redirect_list(node->child[1]) != -1)
				return (e_subshell(node->child[0]));
	}
	return (0);
}

int	last_cmd(t_ast_node *node, int depth)
{
	if (depth == 0) // 단일 명령어
	{
		ft_printf("this is only one cmd\n");
		if (node->child)
		{
			if (node->child[0] && node->child[0]->sym == SIMPLE_COMMAND)
				return (e_simple_cmd(node->child[0]));
			else
				if (e_redirect_list(node->child[1]) != -1)
					return (e_subshell(node->child[0]));
		}
	}
	else
	{
		ft_printf("this is last cmd\n");
		if (node->child)
		{
			if (node->child[0] && node->child[0]->sym == SIMPLE_COMMAND)
				return (e_simple_cmd(node->child[0]));
			else
				if (e_redirect_list(node->child[1]) != -1)
					return (e_subshell(node->child[0]));
		}
	}
	return (0);
}

int	e_pipe_sequence(t_ast_node *node)
{
	t_ast_node	*curr;

	curr = node;
	if (curr->child[1]->child == NULL || curr->child[1]->child[0] == NULL)
		return (last_cmd(curr->child[0], 0)); 
	if (first_cmd(curr->child[0]) == -1)
		return (-1);
	curr = curr->child[1];
	while (curr->child[1]->child && curr->child[1]->child[0])
	{
		if (middle_cmd(curr->child[0]) == -1)
			return (-1);
		curr = curr->child[1];
	}
	return (last_cmd(curr->child[0], 1));
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
