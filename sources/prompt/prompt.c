/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/06/04 15:47:17 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_SIGNAL
#define USE_READLINE
#include "minishell.h"

void	handler(int signo)
{
	if (signo != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
void	set_signal()
{
	signal(SIGINT, handler);
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

int	prompt(void)
{
	char			*line;
	struct termios	old_term;

	set_echoctl(&old_term);
	set_signal();
    while(1)
	{
        line = readline("Nutshell $ \033[s");
        if (!line)
		{
        	printf("\033[u\033[1B\033[1A");
            printf("exit\n");
            exit(-1);
		}
		if (*line != '\0')
			add_history(line);
		free(line);
    }
	restore_echoctl(&old_term);
	return (0);
}
