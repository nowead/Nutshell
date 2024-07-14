/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:05 by damin             #+#    #+#             */
/*   Updated: 2024/07/14 19:11:30 by damin            ###   ########.fr       */
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

# define EXECVE_FAILURE 126
# define FILE_NOT_EXIST_FAILURE 127

// exec_ast.c
void	exec_ast(t_ast *ast, t_shell_ctx *shell_ctx);

// exec_and_or.c
int		exec_and_or(t_ast_node *root, t_shell_ctx *shell_ctx);
int		exec_and_or_(t_ast_node *curr, int prev_result, t_shell_ctx *shell_ctx);

// exec_pipe_sequence.c
int		exec_pipe_sequence(t_ast_node *curr, t_shell_ctx *shell_ctx);

// exec_single_command.c
int		single_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_external_cmd(t_ast_node *curr, t_shell_ctx *shell_ctx);

// exec_multiple_command.c
int		multiple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		execute_middle_commands(t_ast_node **curr, int fd[3], \
size_t *cmd_cnt, t_shell_ctx *shell_ctx);
int		wait_for_all_commands(size_t cmd_cnt, int *status, int *is_signaled);
int		is_there_pipe(t_ast_node *curr);
int     handle_signal(t_shell_ctx *shell_ctx, int signaled_status);

// exec_individual_commands.c
int		first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx);
int		middle_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx);
void	middle_command_child(t_ast_node *curr, int fd[3], \
t_shell_ctx *shell_ctx);
int		last_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx, \
int *is_signaled);
int		save_exit_status(pid_t pid, t_shell_ctx *shell_ctx, int *is_signaled);

// exec_command.c
void	exec_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		count_argument(t_ast_node *curr);
void	execute_argv(char *cmd_name, char **argv, t_shell_ctx *shell_ctx);
void	handle_error(char *cmd_name);

// exec_prefix_and_suffix.c
void	exec_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_cmd_suffix(t_ast_node *curr, char **argv, t_shell_ctx *shell_ctx);
void	add_argument(char **argv, char *arg);
void	exec_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx);

// exec_subshell.c
void	exec_redirect_list(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_subshell(t_ast_node *curr, t_shell_ctx *shell_ctx);

// exec_io_here.c
int		exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx);
int		open_here_doc_tempfile(char **file_name, char *envp[]);
int		create_unique_file(char **file_name, char *home_path);
int		open_tempfile(char **file_name, char *home_path);
void	io_readline(int fd, const char *str);
int		is_there_next_io_here(t_ast_node *curr);

// exec_io_file.c
int		exec_io_file(t_ast_node *node);

// ft_execvpe.c
int		ft_execvpe(const char *file, char *const argv[], char *envp[]);
// ft_getenv.c
char	*ft_getenv(const char *key, char *envp[]);

#endif
