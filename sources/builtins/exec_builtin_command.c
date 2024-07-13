/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:26:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 21:41:58 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	**argv;
	int		ret;
	int		pid;
	int		status;

	ret = -1;
	pid = fork();
	if (pid == -1)
		return (err_return(1, "fork"));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (curr->child_num == 2)
			exec_redirect_in_suffix(curr->child[1], shell_ctx);
		else
		{
			exec_builtin_cmd_prefix(curr->child[0], shell_ctx);
			exec_redirect_in_suffix(curr->child[2], shell_ctx);
		}
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	if (wait(&status) == -1)
		return (-1);
	shell_ctx->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		return (handle_signal(shell_ctx, WTERMSIG(status)));
	if (shell_ctx->exit_status != 0)
		return (shell_ctx->exit_status);
	if (backup_stdin(shell_ctx) == -1)
		err_return(1, "dup");
	argv = (char **)ft_calloc(count_argument(curr) + 2, sizeof(char *));
	if (argv == NULL)
		ret = err_return(1, "malloc");
	if (curr->child_num == 2)
	{
		argv[0] = ft_strdup(curr->child[0]->token->str);
		ret = exec_suffix_without_redirect(curr->child[1], argv, shell_ctx);
	}
	else
	{
		argv[0] = ft_strdup(curr->child[1]->token->str);
		ret = exec_suffix_without_redirect(curr->child[2], argv, shell_ctx);
	}
	if (ret != -1)
		ret = execute_builtin_argv(argv[0], argv, shell_ctx);
	shell_ctx->exit_status = ret;
	ft_free_strs(argv);
	if (restore_stdin(shell_ctx) == -1)
		err_return(1, "dup2");
	return (ret);
}

int	execute_builtin_argv(char *cmd_name, char **argv, t_shell_ctx *shell_ctx)
{
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (exec_export(argv, &(shell_ctx->envp)));
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (exec_unset(argv, &(shell_ctx->envp)));
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		exec_exit(argv, shell_ctx);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (exec_cd(argv, &(shell_ctx->envp)));
	return (-1);
}

int	backup_stdin(t_shell_ctx *shell_ctx)
{
	shell_ctx->stdfd[0]	= dup(STDIN_FILENO);
	if (shell_ctx->stdfd[0] == -1)
		return (-1);
	return (0);
}

int	restore_stdin(t_shell_ctx *shell_ctx)
{
	if (dup2(shell_ctx->stdfd[0], STDIN_FILENO) == -1)
		return (-1);
	if (close(shell_ctx->stdfd[0]) == -1)
		return (-1);
	return (0);
}