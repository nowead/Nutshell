/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:03:24 by macbookair        #+#    #+#             */
/*   Updated: 2024/02/27 14:29:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
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

char	*ft_get_line(t_fdlist **head, t_fdlist *fdnode, char *newline)
{
	char	*line;
	char	*left;

	if (newline == NULL)
	{
		if ((fdnode->save != NULL) && (*(fdnode->save) == '\0'))
			return (ft_free_fdnode(head, fdnode));
		line = gnl_substr(fdnode->save, 0, fdnode->save_size);
		ft_free_fdnode(head, fdnode);
		return (line);
	}
	line = gnl_substr(fdnode->save, 0, newline + 1 - fdnode->save);
	if (line == NULL)
		return (ft_free_fdnode(head, fdnode));
	fdnode->save_len = ft_strlen(newline + 1);
	fdnode->save_size = fdnode->save_len + 1;
	left = gnl_substr(newline + 1, 0, fdnode->save_len);
	if (left == NULL)
	{
		free(line);
		return (ft_free_fdnode(head, fdnode));
	}
	free(fdnode->save);
	fdnode->save = left;
	return (line);
}

t_fdlist	*ft_set_fdnode(t_fdlist **head, int fd)
{
	t_fdlist	*curr;
	t_fdlist	*prev;

	curr = *head;
	prev = NULL;
	while (curr && curr->fd != fd)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		curr = (t_fdlist *)malloc(sizeof(t_fdlist));
		if (NULL == curr)
			return (NULL);
		*curr = (t_fdlist){};
		curr->fd = fd;
		if (*head != NULL)
			prev->next = curr;
		else
			*head = curr;
	}
	return (curr);
}

void	*ft_free_fdnode(t_fdlist **head, t_fdlist *fdnode)
{
	t_fdlist	*curr;
	t_fdlist	*prev;

	curr = *head;
	prev = NULL;
	while (curr && curr != fdnode)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == fdnode)
	{
		if (curr == *head)
			*head = (*head)->next;
		else
			prev->next = curr->next;
		free(curr->save);
		curr->save = NULL;
		free(curr);
		curr = NULL;
	}
	return (NULL);
}

int	ft_bufjoin(t_fdlist *fdnode, char *buf)
{
	char	*joinstr;
	size_t	joinlen;

	joinlen = fdnode->save_len + ft_strlen(buf);
	if (fdnode->save_size < joinlen + 1)
	{
		if (fdnode->save_size == 0)
			fdnode->save_size = joinlen + 1;
		while (fdnode->save_size < joinlen + 1)
			fdnode->save_size *= 2;
		joinstr = (char *)malloc(sizeof(char) * fdnode->save_size);
		if (joinstr == NULL)
			return (-1);
		gnl_strlcpy(joinstr, fdnode->save, fdnode->save_size);
		free(fdnode->save);
		fdnode->save = joinstr;
	}
	gnl_strlcpy(fdnode->save + fdnode->save_len, buf, fdnode->save_size);
	fdnode->save_len = joinlen;
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	int fd[2];

// 	fd[0] = open("text1", O_RDWR);
// 	printf("%s", get_next_line(fd[0]));
// 	fd[1] = open("text2", O_RDWR);
// 	printf("%s", get_next_line(fd[1]));
// 	printf("%s", get_next_line(fd[0]));
// 	printf("%s", get_next_line(fd[1]));
// 	printf("%s", get_next_line(fd[0]));
// 	printf("%s", get_next_line(fd[0]));
// 	printf("%s", get_next_line(fd[0]));
// 	close(fd[0]);
// 	printf("%s", get_next_line(fd[1]));
// 	printf("%s", get_next_line(fd[1]));
// 	printf("%s", get_next_line(fd[1]));

// 	close(fd[1]);
// 	return (0);
// }
