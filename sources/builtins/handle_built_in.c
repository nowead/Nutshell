/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:45:56 by damin             #+#    #+#             */
/*   Updated: 2024/07/11 16:01:19 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_cmd(t_ast_node *curr)
{
	char	*cmd_name;

	if (curr->sym == SUBSHELL)
		return (0);
	if (curr->child_num == 2)
		cmd_name = curr->child[0]->token->str;
	else if (curr->child_num == 3)
		cmd_name = curr->child[1]->token->str;
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (1);
	return (0);
}

int	exec_builtin_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	**argv;
	int		ret;

	argv = (char **)ft_calloc(count_argument(curr) + 2, sizeof(char *));
	if (argv == NULL)
		ret = err_return("malloc");
	if (curr->child_num == 2)
	{
		argv[0] = ft_strdup(curr->child[0]->token->str);
		ret = exec_builtin_cmd_suffix(curr->child[1], argv, shell_ctx);
	}
	else
	{
		argv[0] = ft_strdup(curr->child[1]->token->str);
		ret = exec_builtin_cmd_prefix(curr->child[0], shell_ctx);
		if (ret != -1)
			ret = exec_builtin_cmd_suffix(curr->child[2], argv, shell_ctx);
	}
	if (ret != -1 && execute_builtin_argv(argv[0], argv, shell_ctx) == -1)
		ret = err_return(argv[0]);
	ft_free_strs(argv);
	shell_ctx->exit_status = ret;
	return (ret);
}

int	execute_builtin_argv(char *cmd_name, char **argv, t_shell_ctx *shell_ctx)
{
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (exec_export(argv, &(shell_ctx->envp)));
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (exec_unset(argv, &(shell_ctx->envp)));
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		exec_exit(argv, shell_ctx);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (exec_cd(argv, &(shell_ctx->envp)));
	return (-1);
}

int	exec_builtin_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			if (exec_builtin_io_redirect(curr->child[0], shell_ctx) == -1)
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_builtin_cmd_suffix(t_ast_node *curr, char **argv, \
t_shell_ctx *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
		{
			if (exec_builtin_io_redirect(curr->child[0], shell_ctx) == -1)
				return (-1);
		}
		else if (curr->child[0]->token->type == TOK_WORD)
			add_argument(argv, curr->child[0]->token->str);
		curr = curr->child[1];
	}
	return (0);
}

int	exec_builtin_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == IO_FILE)
		return (exec_builtin_io_file(curr->child[0]));
	else
		return (exec_builtin_io_here(curr->child[0], shell_ctx));
}

int	exec_builtin_io_file(t_ast_node *node)
{
	int	fd;

	if (node->token->type == TOK_LESS)
		fd = open(node->child[0]->token->str, O_RDONLY);
	else if (node->token->type == TOK_GREAT)
		fd = open(node->child[0]->token->str, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token->type == TOK_DGREAT)
		fd = open(node->child[0]->token->str, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (err_return("open"));
	if (node->token->type == TOK_LESS)
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

int	builtin_open_here_doc_tempfile(char **file_name, t_shell_ctx *shell_ctx)
{
	int			fd;
	int			i;
	char		*num;
	char		*home_path;

	home_path = ft_strjoin(ft_getenv("HOME", shell_ctx->envp), "/here_doc_");
	if (home_path == NULL)
		return (err_return("ft_strjoin"));
	i = 0;
	num = ft_itoa(i);
	*file_name = ft_strjoin(home_path, num);
	if (*file_name == NULL)
		return (err_return("ft_strjoin"));
	while (1)
	{
		if (access(*file_name, F_OK) != -1)
		{
			i++;
			free (num);
			free (*file_name);
			num = ft_itoa(i);
			*file_name = ft_strjoin(home_path, num);
			if (*file_name == NULL)
				return (err_return("ft_strjoin"));
		}
		else
		{
			fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				free(*file_name);
				free(home_path);
				return (err_return("open"));
			}
			break ;
		}
	}
	free (home_path);
	return (fd);
}

int	exec_builtin_io_here(t_ast_node *node, t_shell_ctx *shell_ctx)
{
	int				fd;
	char			*file_name;
	struct termios	old_term;
	int				stdin_fd;

	set_echoctl(&old_term, ECHOCTL_OFF);
	fd = builtin_open_here_doc_tempfile(&file_name, shell_ctx);
	if (fd == -1)
		return (err_return("builtin open tempfile"));
	io_readline(fd, node->child[0]->token->str);
	if (close(fd) == -1)
		return (err_return("close"));
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (err_return("open"));
	if (dup2(STDIN_FILENO, stdin_fd) == -1)
		return (err_return("dup2 error"));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (err_return("dup2 error"));
	if (unlink(file_name) == -1)
		return (err_return("unlink"));
	if (close(fd) == -1 || close(STDIN_FILENO) == -1)
		return (err_return("close"));
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		return (err_return("dup2 error"));
	free(file_name);
	return (0);
}
