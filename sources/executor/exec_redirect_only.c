/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_only.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:25:00 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 21:45:53 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect_only(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	struct sigaction action;

    action.sa_handler = here_doc_handler;
    action.sa_flags = 0;
	action.sa_flags &= ~SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) == -1) {
        return (err_return(-1, "sigaction"));
    }
	if (redirect_only_simple_command(curr, shell_ctx))
	{
		set_signal_handler(SIGINT_HANDLER);
		return (-1);
	}
	set_signal_handler(SIGINT_HANDLER);
	return (0);
}

int	redirect_only_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child[0]->sym == SIMPLE_COMMAND)
		curr = curr->child[0];
	if (curr->child[0]->sym == SUBSHELL)
		return (0);
	if (curr->child_num == 2)
	{
		if (exec_cmd_suffix_redirect(curr->child[1], shell_ctx))
			return (-1);
	}
	else if (curr->child_num == 3)
	{
		if (exec_cmd_prefix(curr->child[0], shell_ctx))
			return (-1);
		if (exec_cmd_suffix_redirect(curr->child[2], shell_ctx))
			return (-1);
	}
	else
		if (exec_cmd_prefix(curr->child[0], shell_ctx))
			return (-1);
	return (0);
}

int	open_here_doc_tempfile_read(char **file_name, char *envp[])
{
	int			fd;

	*file_name = ft_strjoin(ft_getenv("HOME", envp), "/.here_doc");
	if (*file_name == NULL)
		return (err_return(-1, "ft_strjoin"));
	fd = open(*file_name, O_RDONLY, 0644);
	if (fd == -1)
	{
		free(*file_name);
		return (err_return(-1, "open_here_doc_tempfile_read"));
	}
	return (fd);
}
