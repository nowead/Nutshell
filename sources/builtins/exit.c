/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/07/18 20:31:19 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_numeric_err_exit(char **argv)
{
	printf("exit\n");
	write(STDERR_FILENO, "Nutshell: exit: ", 16);
	ft_dprintf(2, \
	"Nutshell: exit: %s: numeric argument required\n", argv[1]);
	exit(255);
}

void	exec_exit(char **argv, t_shell_ctx *shell_ctx)
{
	restore_stdfd(shell_ctx);
	restore_echoctl(&(shell_ctx->old_term), shell_ctx->stdfd[0]);
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
