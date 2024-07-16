/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:05:27 by damin             #+#    #+#             */
/*   Updated: 2024/07/16 14:10:01 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

char	*gnl(int fd)
{
	static t_fdlist	*head;
	t_fdlist		*fdnode;
	char			buf[BUFFER_SIZE + 1];
	char			*newline;
	ssize_t			readbyte;

	fdnode = ft_set_fdnode(&head, fd);
	if (NULL == fdnode)
		return (NULL);
	newline = NULL;
	while (1)
	{
		newline = gnl_strchr(fdnode->save, '\n');
		if (newline != NULL)
			break ;
		readbyte = read(fd, buf, BUFFER_SIZE);
        if (g_sigint_flag == 1)
        {
            g_sigint_flag = 0;
            return (ft_free_fdnode(&head, fdnode));
        }
		if (readbyte == -1)
			return (ft_free_fdnode(&head, fdnode));
		if (readbyte == 0)
			break ;
		buf[readbyte] = '\0';
		if (ft_bufjoin(fdnode, buf) == -1)
			return (ft_free_fdnode(&head, fdnode));
	}
	return (ft_get_line(&head, fdnode, newline));
}
