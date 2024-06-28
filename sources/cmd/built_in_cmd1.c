/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/06/28 21:14:35 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_echo(char **argv)
{
	int i;
	int	n_flag_on;

	i = 1;
	n_flag_on = 0;
	while (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
	{
		n_flag_on = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s",argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (!n_flag_on)
		printf("\n");
	exit(EXIT_SUCCESS);
}

void	exec_exit(t_shell_context *shell_ctx)
{
	printf("\033[u\033[1B\033[1A");
	printf("\nexit\n");
	restore_echoctl(&(shell_ctx->old_term));
	exit(EXIT_SUCCESS);
}

void	exec_cd()
{

}

void	exec_pwd()
{

}

void	exec_env(t_shell_context *shell_ctx)
{
	size_t	i;
	char	**envp;

	envp = *(shell_ctx->envp);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

int	exec_export(t_ast_node *curr, char ***envp)
{
	size_t	envp_len;
	char	**new_envp;

	envp_len = ft_strslen(*envp);
	new_envp = (char **)ft_calloc(envp_len + 2, sizeof(char *));
	if (new_envp == NULL)
		return (err_return("malloc"));
	ft_memcpy(new_envp, *envp, envp_len + 2);
	ft_memcpy(new_envp + envp_len, curr->token->str, envp_len + 2);
	free(*envp);
	*envp = new_envp;
	return (0);
}

size_t	ft_strslen(char **strs)
{
	size_t	len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}