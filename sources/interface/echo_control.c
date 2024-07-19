/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:03:37 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/19 13:56:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_echoctl(struct termios *old_term, int echoctl_flag, int stdin_fd)
{
	struct termios	new_term;

	tcgetattr(stdin_fd, old_term);
	tcgetattr(stdin_fd, &new_term);
	if (echoctl_flag == ECHOCTL_OFF)
		new_term.c_lflag &= ~(ECHOCTL);
	else
		new_term.c_lflag |= (ECHOCTL);
	tcsetattr(stdin_fd, TCSANOW, &new_term);
}

void	restore_echoctl(struct termios *old_term, int stdin_fd)
{
	tcsetattr(stdin_fd, TCSANOW, old_term);
}
