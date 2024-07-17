/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:23:33 by damin             #+#    #+#             */
/*   Updated: 2024/07/17 21:30:23 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	g_sigint_flag = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	here_doc_handler(int signo)
{
	(void)signo;
}

void	convert_to_child_process(void)
{
	set_echoctl(NULL, ECHOCTL_ON);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	convert_to_nutshell_terminal(void)
{
	set_echoctl(NULL, ECHOCTL_OFF);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
