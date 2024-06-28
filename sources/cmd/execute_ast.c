/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/28 19:29:28 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define USE_SIGNAL
#include "minishell.h"

void	exec_ast(t_ast *ast, t_shell_context *shell_ctx)
{
	exec_and_or(ast->root, shell_ctx);
}

int	exec_and_or(t_ast_node *root, t_shell_context *shell_ctx)
{
	int	initial_result;

	if (root->child == NULL)
		return (-1);
	initial_result = exec_pipe_sequence(root->child[0], shell_ctx);
	return (exec_and_or_(root->child[1], initial_result, shell_ctx));
}

int exec_and_or_(t_ast_node *curr, int prev_result, t_shell_context *shell_ctx)
{
	int	curr_result;

	if (curr->token && \
	((curr->token->type == AND_IF && prev_result == 0) ||\
	 (curr->token->type == OR_IF && prev_result == -1)))
	{
		curr_result = exec_pipe_sequence(curr->child[0], shell_ctx);
		return (exec_and_or_(curr->child[1], curr_result, shell_ctx));
	}
	return (prev_result);
}

int	exec_pipe_sequence(t_ast_node *curr, t_shell_context *shell_ctx)
{
	if (!is_there_pipe(curr))
		return (single_command(curr->child[0], shell_ctx));
	else
		return (multiple_command(curr, shell_ctx));
}

int	single_command(t_ast_node *curr, t_shell_context *shell_ctx) // command
{
	if (is_builtin_cmd(curr->child[0]))
	{
		if (exec_builtin_simple_command(curr->child[0], shell_ctx) == -1)
			return (-1);
	}
	return (exec_external_cmd(curr, shell_ctx));
}

int	exec_external_cmd(t_ast_node *curr, t_shell_context *shell_ctx)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_echoctl(NULL, ECHOCTL_ON);
		signal(SIGINT, SIG_DFL);
		exec_command(curr, shell_ctx);
	}
	signal(SIGINT, SIG_IGN);
	if (wait(&status) == -1)
		return (-1);
	if (WIFSIGNALED(status))
		printf("\n");
	set_echoctl(NULL, ECHOCTL_OFF);
	set_signal(SIGINT_HANDLER);
	return (0);
}

int	multiple_command(t_ast_node *curr, t_shell_context *shell_ctx)
{
	int				fd[3];
	size_t			cmd_cnt;
	int				status;
	struct termios	old_term;

	signal(SIGINT, SIG_IGN);
	if (first_command(curr->child[0], fd, shell_ctx) == -1)
		return (-1);
	cmd_cnt = 1;
	curr = curr->child[1];
	while (is_there_pipe(curr))
	{
		if (middle_command(curr->child[0], fd, shell_ctx) == -1)
			return (-1);
		cmd_cnt++;
		curr = curr->child[1];
	}
	if (last_command(curr->child[0], fd, shell_ctx) == -1)
		return (-1);
	cmd_cnt++;
	while (cmd_cnt)
	{
		if (wait(&status) == -1)
			return (-1);
		cmd_cnt--;
	}
	if (WIFSIGNALED(status))
		printf("\n");
	set_echoctl(&old_term, ECHOCTL_OFF);
	set_signal(SIGINT_HANDLER);
	return (0);
}

int	is_there_pipe(t_ast_node *curr)
{
	if (curr->child[1]->child)
		return (1);
	else
		return (0);
}

int	first_command(t_ast_node *curr, int fd[3], t_shell_context *shell_ctx)
{
	pid_t			pid;
	struct termios	old_term;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		set_echoctl(&old_term, ECHOCTL_ON);
		signal(SIGINT, SIG_DFL);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			err_ctrl("close", 1, EXIT_FAILURE);
		exec_command(curr, shell_ctx);
	}
	return (0);
}

int	middle_command(t_ast_node *curr, int fd[3], t_shell_context *shell_ctx)
{
	pid_t			pid;
	struct termios	old_term;

	if (close(fd[1]) == -1)
		return (-1);
	fd[2] = fd[0];
	if (pipe(fd) == -1)
		return (-1);
	
	pid = fork();
	if (pid == -1)
	{
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			return (-1);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (dup2(fd[2], STDIN_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			err_ctrl("close", 1, EXIT_FAILURE);
		exec_command(curr, shell_ctx);
	}
	if (close(fd[2]) == -1)
		return (-1);
	return (0);
}

int	last_command(t_ast_node *curr, int fd[3], t_shell_context *shell_ctx)
{
	pid_t			pid;
	struct termios	old_term;

	if (close(fd[1]) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			err_ctrl("dup2", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1)
			err_ctrl("close", 1, EXIT_FAILURE);
		exec_command(curr, shell_ctx);
	}
	if (close(fd[0]) == -1)
		return (-1);
	return (0);
}

void	exec_command(t_ast_node *curr, t_shell_context *shell_ctx)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		exec_simple_command(curr->child[0], shell_ctx);
	else
	{
		exec_redirect_list(curr->child[1]);
		exec_subshell(curr->child[0], shell_ctx);
	}
}

void	exec_redirect_list(t_ast_node *curr)
{
	if (curr->child == NULL)
		return;
	exec_io_redirect(curr->child[0]);
	exec_redirect_list(curr->child[1]);
}

void	exec_subshell(t_ast_node *curr, t_shell_context *shell_ctx)
{
	if (exec_and_or(curr, shell_ctx) == -1)
	{
		perror("subshell");
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}

int	count_argument(t_ast_node *curr)
{
	int	option_cnt;

	if (curr->child_num == 2)
		curr = curr->child[1];
	else
		curr = curr->child[2];
	option_cnt = 0;
	while (curr->child)
	{
		if (curr->child[0]->sym == TERMINAL)
			option_cnt++;
		curr = curr->child[1];
	}
	return (option_cnt);
}

void	execute(char *cmd_name, char **argv, t_shell_context *shell_ctx)
{
	if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name)) == 0)
		exec_echo(argv);
	// else if (ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name)) == 0)
	// 	;
	// else if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name)) == 0)
	// 	;
	else if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)) == 0)
		exit(EXIT_SUCCESS);
	else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)) == 0)
		exit(EXIT_SUCCESS);
	// else if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name)) == 0)
	// 	;
	else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)) == 0)
		exit(EXIT_SUCCESS);
	// else
	else
		ft_execvpe(argv[0], argv, *(shell_ctx->envp));
}

void	exec_simple_command(t_ast_node *curr, t_shell_context *shell_ctx)
{
	char	**argv;

	argv = NULL;
	if (curr->child_num == 1 || curr->child_num == 3)
		exec_cmd_prefix(curr->child[0], shell_ctx);
	argv = (char **)ft_calloc(count_argument(curr) + 2, sizeof(char *));
	if (argv == NULL)
		err_ctrl("malloc failed", 1, EXIT_FAILURE);
	if (curr->child_num == 2)
	{
		argv[0] = curr->child[0]->token->str;
		exec_cmd_suffix(curr->child[1], argv);
	}
	else if(curr->child_num == 3)
	{
		argv[0] = curr->child[1]->token->str;
		exec_cmd_suffix(curr->child[2], argv);
	}
	// int i = 0;
	// while (argv[i])
	// {
	// 	printf("\nargv[%d]:[%s]\n", i, argv[i]);
	// 	i++;
	// }
	if (curr->child_num != 1)
		execute(argv[0], argv, shell_ctx);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

void	exec_cmd_prefix(t_ast_node *curr, t_shell_context *shell_ctx)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			exec_io_redirect(curr->child[0]);
		curr = curr->child[1];
	}
}

void	exec_cmd_suffix(t_ast_node *curr, char **argv)
{
	while (curr->child)
	{
		if (curr->child[0]->sym == IO_REDIRECT)
			exec_io_redirect(curr->child[0]);
		else if (curr->child[0]->token->type == WORD)
			add_argument(argv, curr->child[0]->token->str);
		curr = curr->child[1];
	}
}

void	add_argument(char **argv, char *arg)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	argv[i] = arg;
}

void	exec_io_redirect(t_ast_node *curr)
{
	if (curr->child[0]->sym == IO_FILE)
		exec_io_file(curr->child[0]);
	else
		exec_io_here(curr->child[0]);
}
