/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:11:21 by damin             #+#    #+#             */
/*   Updated: 2024/06/07 19:04:05 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

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

int prompt(void);

#endif