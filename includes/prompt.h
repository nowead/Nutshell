/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mindaewon <mindaewon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:11:21 by damin             #+#    #+#             */
/*   Updated: 2024/06/17 18:10:14 by mindaewon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stdio.h>
# include <stdlib.h>
# include <termios.h>

# ifdef USE_SIGNAL
# include <unistd.h>
# include <signal.h>
# endif

# ifdef USE_READLINE
# include <readline/readline.h>
# include <readline/history.h>
# endif

int prompt(void);

//signal.c
void    handler(int signo);
void	set_signal(pid_t pid);
void	set_echoctl(struct termios *old_term);
void	restore_echoctl(struct termios *old_term);
#endif