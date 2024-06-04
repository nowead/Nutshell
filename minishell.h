/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:11:21 by damin             #+#    #+#             */
/*   Updated: 2024/05/28 17:55:34 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

# ifdef USE_SIGNAL
# include <unistd.h>
# include <termios.h>
# include <signal.h>
// struct sigaction {
//         void     (*sa_handler)(int);
//         void     (*sa_sigaction)(int, siginfo_t *, void *);
//         sigset_t   sa_mask;
//         int        sa_flags;
//         void     (*sa_restorer)(void);
// };
# endif

# ifdef USE_READLINE
# include <readline/readline.h>
# include <readline/history.h>
# endif

#endif