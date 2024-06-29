/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:11:21 by damin             #+#    #+#             */
/*   Updated: 2024/06/28 19:10:16 by damin            ###   ########.fr       */
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

# define SIGINT_HANDLER 0
# define SIGINT_INCOMPLETE_CMD_HANDLER 2
# define ECHOCTL_ON 1
# define ECHOCTL_OFF 0

typedef struct s_shell_context
{
	char            ***envp;
	struct termios  old_term;
}	t_shell_context;

int prompt(char *envp[]);

//signal.c
void    handler(int signo);
void	set_signal(int handler_type);
void	set_echoctl(struct termios *old_term, int echoctl_flag);
void	restore_echoctl(struct termios *old_term);
#endif
