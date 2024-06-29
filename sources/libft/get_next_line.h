/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:03:28 by macbookair        #+#    #+#             */
/*   Updated: 2024/02/27 14:32:25 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_fdlist
{
	int				fd;
	char			*save;
	size_t			save_len;
	size_t			save_size;
	struct s_fdlist	*next;
}	t_fdlist;

char		*get_next_line(int fd);
char		*ft_get_line(t_fdlist **head, t_fdlist *fdnode, char *newline);
int			ft_get_left(t_fdlist *fdnode, char *newline);
t_fdlist	*ft_set_fdnode(t_fdlist **head, int fd);
void		*ft_free_fdnode(t_fdlist **head, t_fdlist *fdnode);
int			ft_bufjoin(t_fdlist *fdnode, char *buf);
char		*gnl_strchr(const char *s, int c);
size_t		gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char		*gnl_substr(char const *s, unsigned int start, size_t len);
//libft.a
size_t		ft_strlen(const char *s);

#endif
