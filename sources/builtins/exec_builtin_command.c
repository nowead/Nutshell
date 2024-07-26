/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:26:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/26 20:07:24 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sym : simple_command
int	exec_builtin_simple_command(t_ast_node *curr, \
t_shell_ctx *shell_ctx)
{
	if (exec_redirections(curr->parent, shell_ctx))
		return (-1);
	return (parent_builtin_simple_command(curr, shell_ctx));
}

int	parent_builtin_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	**argv;
	int		ret;

	argv = NULL;
	ret = expand_parameters_in_simple_command(curr, shell_ctx);
	if (ret != -1)
		argv = (char **)ft_calloc(get_argv_len(curr) + 2, sizeof(char *));
	if (argv == NULL)
		ret = -1;
	if (ret != -1)
		ret = fill_argv(curr, argv);
	if (ret != -1)
		ret = execute_builtin_argv(argv[0], argv, shell_ctx);
	if (ret == -1)
		ret = 1;
	shell_ctx->exit_status = ret;
	ft_free_strs(argv);
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
