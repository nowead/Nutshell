/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:23:33 by damin             #+#    #+#             */
/*   Updated: 2024/07/10 03:11:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal_handler()
{
	set_signal_handler(SIGINT_HANDLER);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_handler(int handler_type)
{
	if (handler_type == SIGINT_HANDLER)
		signal(SIGINT, sigint_handler);
	else if (handler_type == SIGINT_INCOMPLETE_CMD_HANDLER)
		signal(SIGINT, incomplete_cmd_handler);
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
	printf("\033[s");
}

void	incomplete_cmd_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	g_sigint_flag = 1;
	printf("\nNutshell $ ");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\033[2D \b\033[s");
}
