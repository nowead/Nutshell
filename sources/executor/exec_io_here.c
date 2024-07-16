/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/07/16 16:47:25 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx)
{
	int				fd;
	char			*file_name;
	int				backup_pipe_fd[2];

	fd = open_here_doc_tempfile_write(&file_name, shell_ctx->envp);
	if (fd == -1)
		return (free_file_name(file_name));

	if (io_readline(fd, node->child[0]->token->str, shell_ctx))
		return (free_file_name(file_name));
	if (close(fd) == -1 && free_file_name(file_name))
		return (err_return(-1, "close"));
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1 && free_file_name(file_name))
		return (err_return(-1, "open"));
	if (dup2(fd, STDIN_FILENO) && free_file_name(file_name))
		return (err_return(-1, "dup2"));
	if (unlink(file_name) && free_file_name(file_name))
		return (err_return(-1, "unlink"));
	free(file_name);
	return (0);
}

int	free_file_name(char *file_name)
{
	free(file_name);
	return (-1);
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

int	open_here_doc_tempfile_write(char **file_name, char *envp[])
{
	int		fd;

	*file_name = ft_strjoin(ft_getenv("HOME", envp), "/.here_doc");
	if (*file_name == NULL)
		return (err_return(1, "ft_strjoin"));
	fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (err_return(1, "open"));
	return (fd);
}

void	remove_new_line_from_line(char **line)
{
	int		len;

	len = ft_strlen(*line);
	if ((*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
}

int	io_readline(int fd, const char *delimiter, t_shell_ctx *shell_ctx)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		write(shell_ctx->stdfd[1], "> \033[s\b\b", 8);
		write(shell_ctx->stdfd[1], "> ", 2);
		line = get_next_line(shell_ctx->stdfd[0]);
		if (!line)
		{
			if (errno == EINTR)
			{
				restore_stdfd(shell_ctx);
				return (-1);
			}
			ft_printf("\033[u\033[1B\033[1A");
			break ;
		}
		remove_new_line_from_line(&line);
		if (expand_parameters_in_string(&line, shell_ctx) == -1)
			return (err_return(-1, "expand_parameters_in_string"));
		if (ft_strlen(line) == ft_strlen(delimiter) && \
		ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(line);
	return (0);
}
