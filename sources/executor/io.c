/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:51:12 by damin             #+#    #+#             */
/*   Updated: 2024/07/11 21:03:27 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	 USE_READLINE
#include "minishell.h"

void	io_readline(int fd, const char *str)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		printf("> \033[s\b\b");
		line = readline("> ");
		if (!line)
		{
			printf("\033[u\033[1B\033[1A");
			break ;
		}
		if (ft_strlen(line) == ft_strlen(str) && \
		ft_strncmp(line, str, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
}

void	print_fd(int fd)
{
	char	*line;

	line = "none";
	while (line != 0)
	{
		line = get_next_line(fd);
		if (line)
			ft_printf("%s", line);
	}
}

int	open_here_doc_tempfile(char **file_name)
{
	int			fd;
	int			i;
	char		*num;

	i = 0;
	num = ft_itoa(i);
	*file_name = ft_strjoin("here_doc_", num);
	while (1)
	{
		if (access(*file_name, F_OK) != -1)
		{
			i++;
			free (num);
			free (*file_name);
			num = ft_itoa(i);
			*file_name = ft_strjoin("here_doc_", num);
		}
		else
		{
			fd = open(*file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				err_ctrl("open", 1, EXIT_FAILURE);
			break ;
		}
	}
	return (fd);
}

int	exec_io_here(t_ast_node *node)
{
	int				fd;
	char			*file_name;
	struct termios	old_term;
	
	set_echoctl(&old_term, ECHOCTL_OFF);
	fd = open_here_doc_tempfile(&file_name);
    io_readline(fd, node->child[0]->token->str);
    if (dup2(fd, STDIN_FILENO) == -1)
        err_ctrl("dup2 error", 1, EXIT_FAILURE);
	
	if (close(fd) == -1)
		err_ctrl("close", 1, EXIT_FAILURE);
	return (0);
}

int	exec_io_file(t_ast_node *node)
{
	int	fd;

	if (node->token->type == LESS)
		fd = open(node->child[0]->token->str, O_RDONLY);
	else if (node->token->type == GREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token->type == DGREAT)
		fd = open(node->child[0]->token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		err_ctrl("file open error", 1, EXIT_FAILURE);
	if (node->token->type == LESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			err_ctrl("dup2 error", 1, EXIT_FAILURE);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			err_ctrl("dup2 error", 1, EXIT_FAILURE);
	}
	if (close(fd) == -1)
		err_ctrl("file close error ", 1, EXIT_FAILURE);
	return (0);
}
