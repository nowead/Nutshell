/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:23:33 by damin             #+#    #+#             */
/*   Updated: 2024/08/05 17:39:41 by seonseo          ###   ########.fr       */
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
	if (signo != SIGINT)
		return ;
	printf("\n");
	exit(1);
}

void	convert_to_child_process(void)
{
	set_echoctl(NULL, ECHOCTL_ON, STDIN_FILENO);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	convert_to_nutshell_terminal(void)
{
	set_echoctl(NULL, ECHOCTL_OFF, STDIN_FILENO);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
