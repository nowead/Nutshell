/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/07/24 21:59:48 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_numeric_err_exit(char **argv)
{
	printf("exit\n");
	ft_dprintf(2, \
	"Nutshell: exit: %s: numeric argument required\n", argv[1]);
	exit(255);
}

void	exec_exit(char **argv, t_shell_ctx *shell_ctx)
{
	restore_stdfd(shell_ctx);
	restore_echoctl(&(shell_ctx->old_term), shell_ctx->stdfd[0]);
	exec_exit_in_process(argv, shell_ctx);
}

void	exec_exit_in_process(char **argv, t_shell_ctx *shell_ctx)
{
	long	exit_num;

	if (argv[1])
	{
		errno = 0;
		exit_num = ft_strtol(argv[1], NULL, 10);
		if (errno == EINVAL || errno == ERANGE)
			no_numeric_err_exit(argv);
		if (argv[2])
			err_exit("exit\nNutshell: exit: too many arguments", 0, 1);
		else
			exit(ft_atoi(argv[1]));
	}
	exit(shell_ctx->exit_status);
}
