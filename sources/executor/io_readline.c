/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:15:18 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/19 12:33:47 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
