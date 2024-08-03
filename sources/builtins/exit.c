/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/08/04 02:56:03 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_non_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	no_numeric_err_exit(char **argv)
{
	printf("exit\n");
	ft_dprintf(2, \
	"Nutshell: exit: %s: numeric argument required\n", argv[1]);
	exit(255);
}

int	exec_exit(char **argv, t_shell_ctx *shell_ctx)
{
	long	exit_num;

	restore_stdfd(shell_ctx);
	restore_echoctl(&(shell_ctx->old_term), shell_ctx->stdfd[0]);
	if (argv[1])
	{
		errno = 0;
		exit_num = ft_strtol(argv[1], NULL, 10);
		if (is_non_numeric(argv[1]) || errno == ERANGE)
			no_numeric_err_exit(argv);
		if (argv[2])
		{
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("Nutshell: exit: too many arguments", 2);
			return (1);
		}
		else
		{
			printf("exit\n");
			exit(ft_atoi(argv[1]));
		}
	}
	printf("exit\n");
	exit(shell_ctx->exit_status);
	return (0);
}

int	exec_exit_in_process(char **argv, t_shell_ctx *shell_ctx)
{
	long	exit_num;

	if (argv[1])
	{
		errno = 0;
		exit_num = ft_strtol(argv[1], NULL, 10);
		if (is_non_numeric(argv[1]) || errno == ERANGE)
			no_numeric_err_exit(argv);
		if (argv[2])
		{
			ft_putendl_fd("Nutshell: exit: too many arguments", 2);
			return (1);
		}
		else
			exit(ft_atoi(argv[1]));
	}
	exit(shell_ctx->exit_status);
	return (0);
}
