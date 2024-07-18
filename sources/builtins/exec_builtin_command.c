/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:26:51 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 21:08:26 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sym : simple_command
int	exec_builtin_simple_command(t_ast_node *curr, \
t_shell_ctx *shell_ctx)
{
	if (exec_redirect_only(curr->parent, shell_ctx))
		return (-1);
	return (parent_builtin_simple_command(curr, shell_ctx));
}

int	parent_builtin_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	**argv;
	int		ret;

	argv = (char **)ft_calloc(count_argument(curr) + 2, sizeof(char *));
	if (argv == NULL)
		return (err_return(1, "malloc"));
	if (curr->child_num == 2)
	{
		argv[0] = ft_strdup(curr->child[0]->token->str);
		ret = exec_suffix_without_redirect(curr->child[1], argv);
	}
	else
	{
		argv[0] = ft_strdup(curr->child[1]->token->str);
		ret = exec_suffix_without_redirect(curr->child[2], argv);
	}
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
