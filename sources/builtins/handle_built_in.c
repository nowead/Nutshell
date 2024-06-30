/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:45:56 by damin             #+#    #+#             */
/*   Updated: 2024/06/30 20:05:22 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     err_return(char *err_msg)
{
    perror(err_msg);
    return (-1);
}

int     is_builtin_cmd(t_ast_node *curr)
{
    char    *cmd_name;

    if (curr->sym == SUBSHELL)
        return (0);

    if (curr->child_num == 2)
		cmd_name = curr->child[0]->token->str;
	else if(curr->child_num == 3)
		cmd_name = curr->child[1]->token->str;
	if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)) == 0)
        return (1);
	else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)) == 0)
		return (1);
    return (0);
}

int	exec_builtin_simple_command(t_ast_node *curr, t_shell_context *shell_ctx)
{
	char	**argv;

	argv = NULL;
	argv = (char **)ft_calloc(count_argument(curr) + 2, sizeof(char *));
	if (argv == NULL)
        return (err_return("malloc"));
	if (curr->child_num == 2)
	{
		argv[0] = curr->child[0]->token->str;
		if (exec_builtin_cmd_suffix(curr->child[1], argv) == -1)
			return (-1);
	}
	else if(curr->child_num == 3)
	{
		argv[0] = curr->child[1]->token->str;
        if (exec_builtin_cmd_prefix(curr->child[0], shell_ctx) == -1)
			return (-1);
		if (exec_builtin_cmd_suffix(curr->child[2], argv) == -1)
			return (-1);
	}
	if (execute_builtin_argv(argv[0], argv, shell_ctx) == -1)
        return (err_return(argv[0]));
	return (0);
}

int	execute_builtin_argv(char *cmd_name, char **argv, t_shell_context *shell_ctx)
{
	// if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)) == 0)
    //     return (exec_export(argv, shell_ctx->envp));
	// else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)) == 0)
	// 	return (exec_unset(cmd_name, argv, shell_ctx));
	if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)) == 0)
		exec_exit(shell_ctx);
    return (-1);
}

int	exec_builtin_cmd_prefix(t_ast_node *curr, t_shell_context *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (exec_builtin_io_redirect(curr->child[0]) == -1)
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_builtin_cmd_suffix(t_ast_node *curr, char **argv)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
		{
			if (exec_builtin_io_redirect(curr->child[0]) == -1)
				return (-1);
		}
		else if (curr->child[0]->token->type == WORD)
			add_argument(argv, curr->child[0]->token->str);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_builtin_io_redirect(t_ast_node *curr)
{
	if (curr->child[0]->sym == IO_FILE)
		return (exec_builtin_io_file(curr->child[0]));
	else
		return (exec_builtin_io_here(curr->child[0]));
}

int	exec_builtin_io_file(t_ast_node *node)
{
	int	fd;

	if (node->token->type == LESS)
		fd = open(node->child[0]->token->str, O_RDONLY);
	else if (node->token->type == GREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token->type == DGREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (err_return("open"));
	if (node->token->type == LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (err_return("dup2"));
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (err_return("dup2"));
	}
	if (close(fd) == -1)
		return (err_return("close"));
	return (0);
}

int	exec_builtin_io_here(t_ast_node *node)
{
	int				fd;
	struct termios	old_term;

	fd = get_valid_fd();
	set_echoctl(&old_term, ECHOCTL_OFF);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (err_return("dup2"));
	io_readline(fd, node->child[0]->token->str);
	//print_fd(fd);
	// if (close(fd) == -1)
	// 	err_ctrl("close error", 1, EXIT_FAILURE);
	//heredoc_parents(fd);
	return (0);
}
