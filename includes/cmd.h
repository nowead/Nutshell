/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:05 by damin             #+#    #+#             */
/*   Updated: 2024/06/23 22:50:13 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stdio.h>
# include <stdlib.h>

# ifdef USE_SIGNAL
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# endif

# ifdef USE_READLINE
# include <readline/readline.h>
# include <readline/history.h>
# endif

void	err_ctrl(char *err, int sys, int exit_status);

#endif
