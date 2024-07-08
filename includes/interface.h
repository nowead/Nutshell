/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:11:21 by damin             #+#    #+#             */
/*   Updated: 2024/07/08 17:38:04 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SIGINT_HANDLER 0
# define SIGINT_INCOMPLETE_CMD_HANDLER 2
# define ECHOCTL_ON 1
# define ECHOCTL_OFF 0

typedef struct s_shell_ctx
{
	char			**envp;
	int				exit_status;
	struct termios	old_term;
}	t_shell_ctx;

int			run_shell(char *envp[]);
void		init_shell_ctx(t_shell_ctx *shell_ctx, char **envp);
char		**init_envp(char *envp[]);
const char	*get_prompt(int incomplete_cmd);
void		exit_shell(struct termios *old_term);

//signal.c
void		handler(int signo);
void		set_signal(int handler_type);
void		set_echoctl(struct termios *old_term, int echoctl_flag);
void		restore_echoctl(struct termios *old_term);
#endif
