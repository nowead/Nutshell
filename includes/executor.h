/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:05 by damin             #+#    #+#             */
/*   Updated: 2024/07/08 16:38:58 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "interface.h"

// io.c
int		open_here_doc_tempfile(char **file_name, t_shell_ctx *shell_ctx);
int		exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx);
int		exec_io_file(t_ast_node *node);
void	io_readline(int fd, const char *str);
void	print_fd(int fd);

// exec_cmd.c
void	exec_ast(t_ast *ast, t_shell_ctx *shell_ctx);
int		exec_and_or(t_ast_node *root, t_shell_ctx *shell_ctx);
int		exec_and_or_(t_ast_node *curr, int prev_result, t_shell_ctx *shell_ctx);
int		exec_pipe_sequence(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		single_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_external_cmd(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		multiple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		is_there_pipe(t_ast_node *curr);
int		first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx);
int		middle_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx);
int		last_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx);
void	exec_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_redirect_list(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_subshell(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		count_argument(t_ast_node *curr);
void	exec_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	execute_argv(char *cmd_name, char **argv, t_shell_ctx *shell_ctx);
void	exec_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	add_argument(char **argv, char *arg);
void	exec_cmd_suffix(t_ast_node *curr, char **argv, t_shell_ctx *shell_ctx);
void	exec_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx);

// built_in_cmd.c
void	exec_echo(char **argv);
void	exec_exit(t_shell_ctx *shell_ctx);
void	exec_pwd(void);
int		exec_cd(char **argv, char ***envp);
void	exec_env(t_shell_ctx *shell_ctx);
int		exec_export(char **argv, char ***envp);

#endif
