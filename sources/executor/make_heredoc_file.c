/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:16:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/19 13:22:27 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_heredoc_file(t_ast_node *node, t_shell_ctx *shell_ctx, \
char **file_name)
{
	int	fd;
	int	ret;

	ret = 0;
	if (unquote_a_token(node->child[0]->token))
		return (-1);
	set_echoctl(NULL, ECHOCTL_OFF, shell_ctx->stdfd[0]);
	fd = open_here_doc_tempfile(file_name, shell_ctx->envp);
	if (fd == -1)
		return (-1);
	if (io_readline(fd, node->child[0]->token->str, shell_ctx))
	{
		write(shell_ctx->stdfd[1], "\n", 1);
		ret = -1;
	}
	if (close(fd) == -1)
		ret = err_return(-1, "close");
	return (ret);
}

int	open_here_doc_tempfile(char **file_name, char *envp[])
{
	int		fd;
	char	*home_path;

	home_path = ft_strjoin(ft_getenv("HOME", envp), "/.here_doc_");
	if (home_path == NULL)
		return (err_return(-1, "ft_strjoin"));
	fd = create_unique_file(file_name, home_path);
	free(home_path);
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
			return (err_return(-1, "ft_strjoin"));
		if (access(*file_name, F_OK) == -1)
		{
			free (num);
			fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (err_return(-1, "open"));
			break ;
		}
		free (num);
		free (*file_name);
		i++;
	}
	return (fd);
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
				return (-1);
			break ;
		}
		remove_new_line_from_line(&line);
		if (ft_strlen(line) == ft_strlen(delimiter) && \
		ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		if (expand_parameters_in_string(&line, shell_ctx) == -1)
			return (err_return(-1, "expand_parameters_in_string"));
		ft_dprintf(fd, "%s\n", line);
		free(line);
	}
	free(line);
	return (0);
}

void	remove_new_line_from_line(char **line)
{
	int		len;

	len = ft_strlen(*line);
	if ((*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
}
