/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/05/28 18:05:31 by damin            ###   ########.fr       */
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

int	main(void)
{
	char			*input;
	struct termios	term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
    while(1)
	{
        input = readline("Nutshell $ ");
        if (!input)
            break;
        add_history(input);
        free(input);
    }
	return (0);
}