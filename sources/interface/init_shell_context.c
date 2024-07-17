/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_context.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:03:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/17 20:52:19 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_ctx(t_shell_ctx *shell_ctx, char **envp)
{
	shell_ctx->envp = init_envp(envp);
	if (shell_ctx->envp == NULL)
		exit_shell(shell_ctx);
	shell_ctx->exit_status = 0;
}

char	**init_envp(char *envp[])
{
	char	**new_envp;
	size_t	envp_len;
	size_t	i;

	envp_len = ft_strslen(envp);
	new_envp = (char **)ft_calloc(envp_len + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			ft_free_strs(new_envp);
			return (NULL);
		}
		i++;
	}
	return (new_envp);
}
