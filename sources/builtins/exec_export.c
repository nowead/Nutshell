/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:03:57 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/29 20:07:06 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_shell_context *shell_ctx)
{
	printf("\033[u\033[1B\033[1A");
	printf("\nexit\n");
	restore_echoctl(&(shell_ctx->old_term));
	exit(EXIT_SUCCESS);
}

// int	exec_export(char **argv, char ***envp)
// {
	
// }

int	exec_export_single_key(char *arg, char ***envp)
{
	// size_t	envp_len;
	// char	**new_envp;

	// search_env()
	// envp_len = ft_strslen(*envp);
	// new_envp = (char **)ft_calloc(envp_len + 2, sizeof(char *));
	// if (new_envp == NULL)
	// 	return (err_return("malloc"));
	// ft_memcpy(new_envp, *envp, envp_len + 2);
	// ft_memcpy(new_envp + envp_len, curr->token->str, envp_len + 2);
	// free(*envp);
	// *envp = new_envp;
	return (0);
}

char	**search_env(const char *key, char *envp[])
{
	size_t	i;
	size_t	len;

	if (key == NULL)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}
