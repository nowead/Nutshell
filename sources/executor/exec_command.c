/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:05:47 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/26 20:03:32 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		exec_simple_command(curr->child[0], shell_ctx);
	else
		exec_subshell(curr->child[0], shell_ctx);
}

void	exec_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	**argv;

	argv = NULL;
	if (curr->child_num == 1)
		exit(EXIT_SUCCESS);
	if (expand_parameters_in_simple_command(curr, shell_ctx))
		err_exit("malloc failed", 1, EXIT_FAILURE);
	argv = (char **)ft_calloc(get_argv_len(curr) + 1, sizeof(char *));
	if (argv == NULL)
		err_exit("malloc failed", 1, EXIT_FAILURE);
	if (fill_argv(curr, argv))
		exit(EXIT_FAILURE);
	execute_argv(argv[0], argv, shell_ctx);
	handle_error(argv[0]);
}

int	get_argv_len(t_ast_node *curr)
{
	int	argv_len;

	argv_len = 0;
	if (curr->child_num == 2)
	{
		argv_len += curr->child[0]->tokenlist->size;
		curr = curr->child[1];
	}
	else
	{
		argv_len += curr->child[1]->tokenlist->size;
		curr = curr->child[2];
	}
	while (curr->child)
	{
		if (curr->child[0]->sym == TERMINAL)
			argv_len += curr->child[0]->tokenlist->size;
		curr = curr->child[1];
	}
	return (argv_len);
}

void	execute_argv(char *cmd_name, char **argv, t_shell_ctx *shell_ctx)
{
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		exec_echo(argv, shell_ctx->envp);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		exec_cd_in_process(argv, &(shell_ctx->envp));
	else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		exec_export_in_pipe(argv);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		exec_unset_in_process(argv, &(shell_ctx->envp));
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		exec_env(shell_ctx);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		exec_exit_in_process(argv, shell_ctx);
	else
		ft_execvpe(argv[0], argv, shell_ctx->envp);
}

void	handle_error(char *cmd_name)
{
	if (errno == ENOENT || errno == EFAULT)
	{
		if (errno == EFAULT)
			ft_dprintf(STDERR_FILENO, \
			"Nutshell: %s: No such file or directory\n", cmd_name);
		else if (errno == ENOENT)
			ft_dprintf(STDERR_FILENO, \
			"Nutshell: %s: command not found\n", cmd_name);
		exit (FILE_NOT_EXIST_FAILURE);
	}
	ft_dprintf(STDERR_FILENO, "Nutshell: ");
	perror(cmd_name);
	exit(EXECVE_FAILURE);
}
