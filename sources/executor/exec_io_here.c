/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/07/15 16:48:38 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx)
{
	int				fd;
	char			*file_name;

	set_echoctl(NULL, ECHOCTL_OFF);
	fd = open_here_doc_tempfile(&file_name, shell_ctx->envp);
	io_readline(fd, node->child[0]->token->str, shell_ctx);
	if (close(fd) == -1)
		err_exit("close", 1, EXIT_FAILURE);
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		err_exit("open", 1, EXIT_FAILURE);
	shell_ctx->stdfd[0] = dup(STDIN_FILENO);
	if (shell_ctx->stdfd[0] == -1)
		err_exit("dup2 error", 1, EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		err_exit("dup2 error", 1, EXIT_FAILURE);
	if (unlink(file_name) == -1)
		err_exit("unlink", 1, EXIT_FAILURE);
	if (is_there_next_io_here(node))
		if (dup2(shell_ctx->stdfd[0], STDIN_FILENO) == -1)
			err_exit("dup2 error", 1, EXIT_FAILURE);
	if (close(fd) == -1 || close(shell_ctx->stdfd[0]) == -1)
		err_exit("close", 1, EXIT_FAILURE);
	free(file_name);
	return (0);
}

int	is_there_next_io_here(t_ast_node *curr)
{
	curr = curr->parent->parent;
	if (curr->child && curr->child[1])
		curr = curr->child[1];
	else
		return (0);
	if (curr->child && curr->child[0])
		curr = curr->child[0];
	else
		return (0);
	if (curr->sym == IO_REDIRECT && curr->child[0]->sym == IO_HERE)
		return (1);
	return (0);
}

int	open_here_doc_tempfile(char **file_name, char *envp[])
{
	int			fd;
	char		*home_path;

	home_path = ft_strjoin(ft_getenv("HOME", envp), "/.here_doc_");
	if (home_path == NULL)
		err_exit("ft_strjoin", 1, EXIT_FAILURE);
	fd = create_unique_file(file_name, home_path);
	free (home_path);
	return (fd);
}

int	create_unique_file(char **file_name, char *home_path)
{
	size_t	i;
	int		fd;
	char	*num;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		*file_name = ft_strjoin(home_path, num);
		if (*file_name == NULL)
			err_exit("ft_strjoin", 1, EXIT_FAILURE);
		if (access(*file_name, F_OK) == -1)
		{
			free (num);
			fd = open_tempfile(file_name, home_path);
			break ;
		}
		free (num);
		free (*file_name);
		i++;
	}
	return (fd);
}

int	open_tempfile(char **file_name, char *home_path)
{
	int	fd;

	fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(home_path);
		free(file_name);
		err_exit("open", 1, EXIT_FAILURE);
	}
	return (fd);
}

void	io_readline(int fd, const char *str, t_shell_ctx *shell_ctx)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		printf("> \033[s\b\b");
		line = readline("> ");
		if (!line)
		{
			ft_printf("\033[u\033[1B\033[1A");
			break ;
		}
		if (expand_parameters_in_string(&line, shell_ctx) == -1)
			err_exit("expand_parameters_in_string", 1, EXIT_FAILURE);
		if (ft_strlen(line) == ft_strlen(str) && \
		ft_strncmp(line, str, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(line);
}
