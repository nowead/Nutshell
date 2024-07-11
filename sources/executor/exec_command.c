/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 04:05:47 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/11 16:45:52 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		exec_simple_command(curr->child[0], shell_ctx);
	else
	{
		exec_redirect_list(curr->child[1], shell_ctx);
		exec_subshell(curr->child[0], shell_ctx);
	}
}

void	exec_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	char	**argv;

	argv = NULL;
	if (curr->child_num == 1 || curr->child_num == 3)
		exec_cmd_prefix(curr->child[0], shell_ctx);
	if (curr->child_num == 1)
		exit(EXIT_SUCCESS);
	argv = (char **)ft_calloc(count_argument(curr) + 2, sizeof(char *));
	if (argv == NULL)
		err_exit("malloc failed", 1, EXIT_FAILURE);
	if (curr->child_num == 2)
	{
		argv[0] = curr->child[0]->token->str;
		exec_cmd_suffix(curr->child[1], argv, shell_ctx);
	}
	else if (curr->child_num == 3)
	{
		argv[0] = curr->child[1]->token->str;
		exec_cmd_suffix(curr->child[2], argv, shell_ctx);
	}
	if (curr->child_num != 1)
		execute_argv(argv[0], argv, shell_ctx);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

int	count_argument(t_ast_node *curr)
{
	int	arg_cnt;

	if (curr->child_num == 2)
		curr = curr->child[1];
	else
		curr = curr->child[2];
	arg_cnt = 0;
	while (curr->child)
	{
		if (curr->child[0]->sym == TERMINAL)
			arg_cnt++;
		curr = curr->child[1];
	}
	return (arg_cnt);
}

void	execute_argv(char *cmd_name, char **argv, t_shell_ctx *shell_ctx)
{
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		exec_echo(argv);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		exec_cd_in_process(argv, &(shell_ctx->envp));
	else if (ft_strncmp(cmd_name, "pwd", 3) == 0)
		exec_pwd();
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		exec_export_in_process(argv);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		exec_unset_in_process(argv, &(shell_ctx->envp));
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		exec_env(shell_ctx);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		exec_exit_in_process(argv);
	else
		ft_execvpe(argv[0], argv, shell_ctx->envp);
}
