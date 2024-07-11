/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/07/11 16:02:04 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(char **argv, t_shell_ctx *shell_ctx)
{
	printf("\033[u\033[1B\033[1A");
	printf("\nexit\n");
	restore_echoctl(&(shell_ctx->old_term));
	if (argv[1])
		exit(ft_atoi(argv[1]));
	else
		exit(EXIT_SUCCESS);
}

void	exec_exit_in_process(char **argv)
{
	if (argv[1])
		exit(ft_atoi(argv[1]));
	else
		exit(EXIT_SUCCESS);
}
