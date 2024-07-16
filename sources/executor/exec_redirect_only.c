/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_only.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:25:00 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 12:44:46 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// curr->sym == command
int	exec_redirect_only(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	int		pid;
	int		status;
	int		fd;
	char	*file_name;

	pid = fork();
	if (pid == -1)
		return (err_return(1, "fork"));
	if (pid == 0)
		redirect_only_simple_command(curr, shell_ctx);

	signal(SIGINT, SIG_IGN);
	if (wait(&status) == -1)
		return (-1);
	shell_ctx->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && restore_stdfd(shell_ctx) == 0)
		if (handle_signal(curr, shell_ctx, WTERMSIG(status)) == 0)
			return (-1);
	if (shell_ctx->exit_status != 0)
		return (shell_ctx->exit_status);

	fd = open_here_doc_tempfile_read(&file_name, shell_ctx->envp);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO))
		return (-1);
	if (close(fd) == -1)
		return (-1);
	if (unlink(file_name) == -1)
		return (-1);
	return (0);
}

// curr->sym == command
void	redirect_only_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	signal(SIGINT, SIG_DFL);
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		curr = curr->child[0];
	if (curr->child_num == 2)
		exec_cmd_suffix_redirect(curr->child[1], shell_ctx);
	else if (curr->child_num == 3)
	{
		exec_cmd_prefix(curr->child[0], shell_ctx);
		exec_cmd_suffix_redirect(curr->child[2], shell_ctx);
	}
	else
		exec_cmd_prefix(curr->child[0], shell_ctx);
	exit(EXIT_SUCCESS);
}

int	open_here_doc_tempfile_read(char **file_name, char *envp[])
{
	int			fd;

	*file_name = ft_strjoin(ft_getenv("HOME", envp), "/.here_doc");
	if (*file_name == NULL)
		return (err_return(1, "ft_strjoin"));
	fd = open(*file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (err_return(1, "open_here_doc_tempfile_read"));
	return (fd);
}
