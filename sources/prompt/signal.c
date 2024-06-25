/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:23:33 by damin             #+#    #+#             */
/*   Updated: 2024/06/25 16:26:25 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_SIGNAL
#define	USE_READLINE
#include "minishell.h"

void	handler(int signo)
{
	if (signo != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	printf("\033[s");
}

void	child_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_printf("child_handler\n");
	exit(128 + SIGINT);
}

void	incomplete_cmd_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	sigint_flag = 1;
	printf("\nNutshell $ ");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\033[2D \b\033[s");
}

void	set_signal(int handler_type)
{
	if (handler_type == SIGINT_HANDLER)
		signal(SIGINT, handler);
	else if (handler_type == SIGINT_CHILD_HANDLER)
		signal(SIGINT, child_handler);
	else if(handler_type == SIGINT_INCOMPLETE_CMD_HANDLER)
		signal(SIGINT, incomplete_cmd_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_echoctl(struct termios *old_term)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, old_term);
    tcgetattr(STDIN_FILENO, &new_term);
    new_term.c_lflag &= ~(ECHOCTL);
    //new_term->c_lflag &= ~(ICANON | ECHOCTL); //?CANONICAL mode on/off
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void	restore_echoctl(struct termios *old_term)
{
    tcsetattr(STDIN_FILENO, TCSANOW, old_term);
}
