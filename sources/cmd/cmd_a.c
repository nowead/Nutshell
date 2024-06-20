/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/20 11:50:12 by damin            ###   ########.fr       */
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
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	old_size = ft_strlen(ptr) + 1;
	if (new_size < old_size)
		old_size = new_size;
    ft_memcpy(new_ptr, ptr, old_size);
    free(ptr);
	return (new_ptr);
}

int	e_assignment_word(t_ast_node *curr)
{
	return (0);
}

int	e_io_redirect(t_ast_node *curr)
{
	if (curr->child[0]->sym == IO_FILE)
		return (e_io_file(curr->child[0]));
	else if (curr->child[0]->sym == IO_HERE)
		return (e_io_here(curr->child[0]));
	return (-1);
}

int	e_redirect_list(t_ast_node *curr)
{
	int	ret;

	ret = -1;
	if (curr == NULL)
		return (0);
	if (curr->child)
	{
		if (curr->child[0])
			ret = e_io_redirect(curr->child[0]);
		if (curr->child[1] && ret != -1)
			return (e_redirect_list(curr->child[1]));
	}
	return (ret);
}

int	e_cmd_suffix(t_ast_node *curr, char **option)
{
	size_t	dst_size;

	if (curr != NULL && curr->child)
	{
		if (curr->child[0] && curr->child[0]->sym == IO_REDIRECT)
		{
			if (e_io_redirect(curr->child[0]) == -1)
				return (-1);
			if (e_cmd_suffix(curr->child[1], option) == -1)
				return (-1);
		}
		else if (curr->child[0] && curr->child[0]->sym == TERMINAL)
		{
			dst_size = ft_strlen(*option) + ft_strlen(curr->child[0]->token->str) + 2;
			*option = (char *)ft_realloc(*option, dst_size);
			if (*option == NULL)
				return (-1);
			ft_strlcat(*option, " ", ft_strlen(*option) + 2);
			ft_strlcat(*option, curr->child[0]->token->str, dst_size);
			if (e_cmd_suffix(curr->child[1], option) == -1)
				return (-1);
		}
	}
	return (0);
}

int	e_cmd_name(t_ast_node *curr, char **option)
{
	char	**options;

	printf("[cmd_name:%s] : [cmd_options:%s]\n", curr->token->str, *option);
	options = ft_split(*option, ' ');
	if (options == NULL)
		return (-1);
	return (0);
}

int	e_cmd_prefix_(t_ast_node *curr)
{
	int	ret;

	ret  = -1;
	if (curr == NULL)
		return (0);
	if (curr->child)
	{
		if (curr->child[0] && curr->child[0]->sym == IO_REDIRECT)
			ret = e_io_redirect(curr->child[0]);
		else if (curr->child[0] && curr->child[0]->sym == ASSIGNMENT_WORD)
			ret = e_assignment_word(curr->child[0]);
		if (curr->child[1] && ret != -1)
			return (e_cmd_prefix_(curr->child[1]));
	}
	return (0);
}

int	e_cmd_prefix(t_ast_node *curr)
{
	int	ret;

	ret = -1;
	if (curr->child[0] && curr->child[0]->sym == IO_REDIRECT)
		ret = e_io_redirect(curr->child[0]);
	else if (curr->child[0] && curr->child[0]->sym == ASSIGNMENT_WORD)
		ret = e_assignment_word(curr->child[0]);
	if (curr->child[1] && ret != -1)
		return (e_cmd_prefix_(curr->child[1]));
	return (ret);
}

int e_simple_cmd(t_ast_node *curr)
{
	char	**option;
	int		ret;

	ret = -1;
	option = (char **)malloc(sizeof(char *));
	if (option == NULL)
		return (-1);
	*option = (char *)ft_calloc(1, sizeof(char));
	if (*option == NULL)
		return (-1);
	if (option == NULL)
		return (-1);
	if (curr->child[0]->sym == CMD_PREFIX && curr->child[1] == NULL)
		ret = e_cmd_prefix(curr->child[0]);
	else if(curr->child[0]->sym == CMD_NAME)
	{
		if (e_cmd_suffix(curr->child[1], option) != -1)
			ret = (e_cmd_name(curr->child[0], option));
	}
	else
	{
		if (e_cmd_prefix(curr->child[0]) != -1)
			if (e_cmd_suffix(curr->child[2], option) != -1)
				ret = e_cmd_name(curr->child[1], option);
	}
	free(*option);
	free(option);
	return (ret);
}

int	e_subshell(t_ast_node *node)
{
	return (0);
}

int	exec_cmd(t_ast_node *curr)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		return (e_simple_cmd(curr->child[0]));
	else
		if (e_redirect_list(curr->child[1]) != -1)
			return (e_subshell(curr->child[0]));
	return (-1);
}

int	first_cmd(t_ast_node *curr, int fd[3])
{
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ft_printf("this is first_cmd\n");
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		return (exec_cmd(curr));
	}
	return (0);
}

int	middle_cmd(t_ast_node *curr, int fd[3])
{
	pid_t	pid;

	if (close(fd[1]) == -1) // fd[0] shouldn't be closed
		return (-1);
	fd[2] = fd[0];
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			return (-1);
		return (-1);
	}
	if (pid == 0)
	{
		ft_printf("this is middle_cmd\n");
		if (dup2(fd[2], STDIN_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		return (exec_cmd(curr));
	}
	if (close(fd[2]) == -1)
		return (-1);
	return (0);
}

int	last_cmd(t_ast_node *curr, int fd[3])
{
	pid_t	pid;

	if (close(fd[1]) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]); // fd[1], fd[2] are already closed
		return (-1);
	}
	if (pid == 0)
	{
		ft_printf("this is last cmd\n");
		if (dup2(fd[0], STDIN_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		return (exec_cmd(curr));
	}
	if (close(fd[0]) == -1)
		return (-1);
	return (0);
}

int	single_cmd(t_ast_node *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		ft_printf("this is only one command\n");
		return (exec_cmd(curr));
	}
	return (0);
}

int	is_there_pipe(t_ast_node *curr)
{
	if (curr->child[1]->child && curr->child[1]->child[0])
		return (1);
	else
		return (0);
}

int	e_pipe_sequence(t_ast_node *curr)
{
	int			fd[3];

	if (!is_there_pipe(curr))
		return (single_cmd(curr->child[0]));
	
	if (first_cmd(curr->child[0], fd) == -1)
		return (-1);
	curr = curr->child[1];
	while (is_there_pipe(curr))
	{
		if (middle_cmd(curr->child[0], fd) == -1)
			return (-1);
		curr = curr->child[1];
	}
	return (last_cmd(curr->child[0], fd));
}

int e_and_or_(t_ast_node *curr, int ret_pipe_sequence)
{
	int	ret_new_pipe_sequence;

	if (curr == NULL)
		return (ret_pipe_sequence);
	ret_new_pipe_sequence = 0;
	if (curr->token && \
	((curr->token->type == AND_IF && ret_pipe_sequence == 0) ||\
	 (curr->token->type == OR_IF && ret_pipe_sequence == -1)))
	{
		if (curr->child)
		{
			ret_new_pipe_sequence = e_pipe_sequence(curr->child[0]);
			return (e_and_or_(curr->child[1], ret_new_pipe_sequence));
		}
	}
	return (ret_pipe_sequence);
}

int	e_and_or(t_ast_node *curr)
{
	int	ret_pipe_sequence;

	ret_pipe_sequence= -1;
	if (curr->child)
	{
		ret_pipe_sequence = e_pipe_sequence(curr->child[0]);
		return (e_and_or_(curr->child[1], ret_pipe_sequence));
	}
	return (ret_pipe_sequence);
}
