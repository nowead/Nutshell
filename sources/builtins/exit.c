/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/07/17 20:33:41 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_numeric_err_exit(char **argv)
{
	ft_dprintf(2, \
	"exit\nNutshell: exit: %s: numeric argument required\n", \
	argv[1]);
	exit(255);
}

void	exec_exit(char **argv, t_shell_ctx *shell_ctx)
{
	restore_echoctl(&(shell_ctx->old_term));
	exec_exit_in_process(argv);
}

void	exec_exit_in_process(char **argv)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				no_numeric_err_exit(argv);
			i++;
		}
		if (argv[2])
			err_exit("exit\nNutshell: exit: too many arguments", 0, 1);
		if (ft_atoi(argv[1]) < 0)
			no_numeric_err_exit(argv);
		else
			exit(ft_atoi(argv[1]));
	}
	exit(EXIT_SUCCESS);
}
