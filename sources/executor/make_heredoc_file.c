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
	int		fd;
	int		ret;
	pid_t	pid;

	ret = 0;
	if (unquote_a_token(node->child[0]->token))
		return (-1);
	set_echoctl(NULL, ECHOCTL_OFF, shell_ctx->stdfd[0]);
	fd = open_here_doc_tempfile(file_name, shell_ctx->envp);
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		ret = err_return(-1, "fork");
	else if (pid == 0)
	{
		signal(SIGINT, here_doc_handler);
		io_readline(fd, node->child[0]->token->str, shell_ctx);
	}
	if (ret != -1)
		ret = wait_fore_here_doc_child();
	if (close(fd) == -1)
		ret = err_return(-1, "close");
	return (ret);
}

int	wait_fore_here_doc_child(void)
{
	int	ret;
	int	status;

	signal(SIGINT, SIG_IGN);
	if (wait(&status) == -1)
		ret = err_return(-1, "wait");
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = -1;
	signal(SIGINT, sigint_handler);
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

void	io_readline(int fd, const char *delimiter, t_shell_ctx *shell_ctx)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(delimiter) && \
		ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
			break ;
		if (expand_parameters_in_string(&line, shell_ctx) == -1)
			err_exit("expand_parameters_in_string", 1, -1);
		if (ft_dprintf(fd, "%s\n", line) == -1)
			err_exit("ft_dprintf", 1, -1);
		free(line);
	}
	free(line);
	exit(0);
}
