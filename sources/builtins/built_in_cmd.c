/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/07/04 17:41:33 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void    exec_echo(char **argv)
{
	int i;
	int	n_flag_on;

	i = 1;
	n_flag_on = 0;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		n_flag_on = 1;
		i++;
	}
	while (argv[i] || (argv[i] && argv[i][0] == '\0'))
	{
		printf("%s",argv[i]);
		i++;
		if (argv[i] || (argv[i] && argv[i][0] == '\0'))
			printf(" ");
	}
	if (!n_flag_on)
		printf("\n");
	exit(EXIT_SUCCESS);
}

void	exec_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		err_ctrl("pwd", 1, EXIT_FAILURE);
    printf("%s\n", cwd);
	free(cwd);
	exit(EXIT_SUCCESS);
}

void	exec_env(t_shell_context *shell_ctx)
{
	size_t	i;
	char	**envp;

	envp = shell_ctx->envp;
	printf("\n====envp_len:%zu====\n\n", ft_strslen(envp));
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

void	exec_exit(t_shell_context *shell_ctx)
{
	printf("\033[u\033[1B\033[1A");
	printf("\nexit\n");
	restore_echoctl(&(shell_ctx->old_term));
	exit(EXIT_SUCCESS);
}
