/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:03:37 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/17 13:20:44 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_echoctl(struct termios *old_term, int echoctl_flag)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, old_term);
	tcgetattr(STDIN_FILENO, &new_term);
	if (echoctl_flag == ECHOCTL_OFF)
		new_term.c_lflag &= ~(ECHOCTL| ICANON);
	else
		new_term.c_lflag |= (ECHOCTL| ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void	restore_echoctl(struct termios *old_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old_term);
}
