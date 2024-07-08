/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/07/08 16:41:31 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint_flag = 0;

static void	print_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

int	run_shell(char *envp[])
{
	char			*line;
	char			*old_line;
	char			*new_line;
	t_ast			*ast;
	int				incomplete_cmd;
	t_shell_ctx		shell_ctx;

	set_echoctl(&(shell_ctx.old_term), ECHOCTL_OFF);
	set_signal(SIGINT_HANDLER);
	init_shell_ctx(&shell_ctx, envp);
	incomplete_cmd = 0;
	while (1)
	{
		if (!incomplete_cmd)
			printf("Nutshell $ \033[s\b\b\b\b\b\b\b\b\b\b\b");
		else
			printf("> \033[s\b\b");
		line = readline(get_prompt(incomplete_cmd));
		if (g_sigint_flag == 1)
		{
			if (incomplete_cmd == 1)
			{
				if (old_line)
					free(old_line);
				set_signal(SIGINT_HANDLER);
				incomplete_cmd = 0;
			}
			shell_ctx.exit_status = 1;
			g_sigint_flag = 0;
		}
		if (!line)
		{
			if (!incomplete_cmd)
				exit_shell(&(shell_ctx.old_term));
			else
			{
				incomplete_cmd = 0;
				ft_dprintf(2, "\033[u\033[1B\033[1A");
				ft_dprintf(2, \
				"nutshell: syntax error: unexpected end of file\n");
				continue ;
			}
		}
		if (incomplete_cmd)
		{
			new_line = ft_strjoin(old_line, line);
			if (new_line == NULL)
			{
				incomplete_cmd = 0;
				perror("ft_strjoin");
				continue ;
			}
			free(old_line);
			free(line);
			line = new_line;
			incomplete_cmd = 0;
		}
		ast = parse(line, &incomplete_cmd, &shell_ctx);
		if (incomplete_cmd)
		{
			set_signal(SIGINT_INCOMPLETE_CMD_HANDLER);
			old_line = line;
			continue ;
		}
		else
			set_signal(SIGINT_HANDLER);
		if (ast == NULL)
			continue ;
		exec_ast(ast, &shell_ctx);
		clear_ast(ast);
		add_history(line);
		free(line);
	}
	return (0);
}

void	init_shell_ctx(t_shell_ctx *shell_ctx, char **envp)
{
	shell_ctx->envp = init_envp(envp);
	if (shell_ctx->envp == NULL)
		exit_shell(&(shell_ctx->old_term));
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

const char	*get_prompt(int incomplete_cmd)
{
	if (incomplete_cmd)
		return ("> ");
	else
		return ("Nutshell $ ");
}

void	exit_shell(struct termios *old_term)
{
	printf("\033[u\033[1B\033[1A");
	printf("exit\n");
	restore_echoctl(old_term);
	exit(-1);
}
