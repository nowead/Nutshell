/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/23 22:49:39 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ast(t_ast *ast)
{
	print_ast(ast->root, 0);
	print_tokenlist(ast->tokenlist);
	ft_printf("\n\n");
	exec_and_or(ast->root);
}

int	exec_and_or(t_ast_node *root)
{
	int	initial_result;

	if (root->child == NULL)
		return (-1);
	initial_result = exec_pipe_sequence(root->child[0]);
	return (exec_and_or_(root->child[1], initial_result));
}

int exec_and_or_(t_ast_node *curr, int prev_result)
{
	int	curr_result;

	if (curr->token && \
	((curr->token->type == AND_IF && prev_result == 0) ||\
	 (curr->token->type == OR_IF && prev_result == -1)))
	{
		curr_result = exec_pipe_sequence(curr->child[0]);
		return (exec_and_or_(curr->child[1], curr_result));
	}
	return (prev_result);
}

int	exec_pipe_sequence(t_ast_node *curr)
{
	if (!is_there_pipe(curr))
		return (single_command(curr->child[0]));
	else
		if (multiple_command(curr) == -1)
			return (-1);	
	return (0);
}

int	single_command(t_ast_node *curr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec_command(curr);
	return (0);
}

int	multiple_command(t_ast_node *curr)
{
	int		fd[3];
	size_t	cmd_cnt;

	if (first_command(curr->child[0], fd) == -1)
		return (-1);
	cmd_cnt = 1;
	curr = curr->child[1];
	while (is_there_pipe(curr))
	{
		if (middle_command(curr->child[0], fd) == -1)
			return (-1);
		cmd_cnt++;
		curr = curr->child[1];
	}
	if (last_command(curr->child[0], fd) == -1)
		return (-1);
	cmd_cnt++;
	while (cmd_cnt)
	{
		if (wait(NULL) == -1)
			return (-1);
		cmd_cnt--;
	}
}

int	is_there_pipe(t_ast_node *curr)
{
	if (curr->child[1]->child)
		return (1);
	else
		return (0);
}

int	first_command(t_ast_node *curr, int fd[3])
{
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			err_ctrl("close", 1, EXIT_FAILURE);
		exec_command(curr);
	}
	return (0);
}

int	middle_command(t_ast_node *curr, int fd[3])
{
	pid_t	pid;

	if (close(fd[1]) == -1)
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
		if (dup2(fd[2], STDIN_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			err_ctrl("close", 1, EXIT_FAILURE);
		exec_command(curr);
	}
	if (close(fd[2]) == -1)
		return (-1);
	return (0);
}

int	last_command(t_ast_node *curr, int fd[3])
{
	pid_t	pid;

	if (close(fd[1]) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (close(fd[0] == -1))
			err_ctrl("close", 1, EXIT_FAILURE);
		exec_command(curr);
	}
	if (close(fd[0]) == -1)
		return (-1);
	return (0);
}

void	exec_command(t_ast_node *curr)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		exec_simple_command(curr->child[0]);
	else
	{
		exec_redirect_list(curr->child[1]);
		exec_subshell(curr->child[0]);
	}
}

void	exec_redirect_list(t_ast_node *curr)
{
	if (curr->child == NULL)
		return;
	exec_io_redirect(curr->child[0]);
	exec_redirect_list(curr->child[1]);
}

int	exec_subshell(t_ast_node *curr)
{
	return (exec_and_or(curr));
}

int exec_simple_command(t_ast_node *curr)
{
	char	**argv;
	char	*cmd_name;

	argv = NULL;
	if(curr->child_num == 3)
	{
		exec_cmd_prefix(curr->child[0], argv);
		cmd_name = curr->child[1]->token->str;
		add_argument(cmd_name, argv);
		exec_cmd_suffix(curr->child[2], argv);
	}
	else if (curr->child_num == 1)
		e_cmd_prefix(curr->child[0]);
	else
	{
		cmd_name = curr->child[0]->token->str;
		add_argument(cmd_name, argv);
		exec_cmd_suffix(curr->child[1], argv);
	}
	if (curr->child_num != 1)
		execvp(cmd_name, argv);
	return (-1);
}

void	exec_cmd_prefix(t_ast_node *curr)
{
	while (curr->child && curr->child[1])
	{
		if (curr->child[0] && curr->child[0]->sym == IO_REDIRECT)
			exec_io_redirect(curr->child[0]);
		else if (curr->child[0] && curr->child[0]->sym == ASSIGNMENT_WORD)
			exec_assignment_word(curr->child[0]);
		if (curr->child[1])
			return (exec_cmd_prefix_(curr->child[1]));
	}
}

void	exec_cmd_suffix(t_ast_node *curr, char **option)
{
	size_t	dst_size;

	if (curr != NULL && curr->child)
	{
		if (curr->child[0] && curr->child[0]->sym == IO_REDIRECT)
		{
			exec_io_redirect(curr->child[0]);
			exec_cmd_suffix(curr->child[1], option);
		}
		else if (curr->child[0] && curr->child[0]->sym == TERMINAL)
		{
			dst_size = ft_strlen(*option) + ft_strlen(curr->child[0]->token->str) + 2;
			*option = (char *)ft_realloc(*option, dst_size);
			if (*option == NULL)
				err_ctrl("malloc", 1, EXIT_FAILURE);
			ft_strlcat(*option, " ", ft_strlen(*option) + 2);
			ft_strlcat(*option, curr->child[0]->token->str, dst_size);
			e_cmd_suffix(curr->child[1], option);
		}
	}
}

void	exec_io_redirect(t_ast_node *curr)
{
	if (curr->child[0]->sym == IO_FILE)
		return (e_io_file(curr->child[0]));
	else if (curr->child[0]->sym == IO_HERE)
		return (e_io_here(curr->child[0]));
}

void	exec_assignment_word(t_ast_node *curr)
{
	return;
}

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
