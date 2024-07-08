/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:15:41 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 17:30:30 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

void	err_exit(char *err, int sys, int exit_status);
int		err_return(char *err_msg);
void	ft_free_strs(char *strs[]);
int		ft_print_strs(char **strs);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strslen(char **strs);
// int		print_tokenlist(t_tokenlist *tokenlist);

#endif
