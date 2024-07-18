/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:05 by damin             #+#    #+#             */
/*   Updated: 2024/07/18 17:06:13 by seonseo          ###   ########.fr       */
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
int		handle_signal(t_shell_ctx *shell_ctx, int signaled_status);

// get_here_doc_input.c
int		get_here_doc_input(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		search_get_heredoc_filename(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_cmd_prefix_hd(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_cmd_suffix_redirect_hd(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_io_redirect_hd(t_ast_node *curr, t_shell_ctx *shell_ctx);

// exec_individual_commands.c
int		first_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx);
int		middle_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx);
int		last_command(t_ast_node *curr, int fd[3], t_shell_ctx *shell_ctx, \
int *is_signaled);
int		save_exit_status(pid_t pid, t_shell_ctx *shell_ctx, int *is_signaled);

// pipe_redirection.c
int		pipe_redirect_first(int fd[3]);
int		pipe_redirect_middle(int fd[3]);
int		pipe_redirect_last(int fd[3]);

// exec_command.c
void	exec_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		count_argument(t_ast_node *curr);
void	execute_argv(char *cmd_name, char **argv, t_shell_ctx *shell_ctx);
void	handle_error(char *cmd_name);

// exec_redirect_only.c
int		exec_redirect_only(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		redirect_only_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		open_here_doc_tempfile_read(char **file_name, char *envp[]);

// exec_affixes.c
int		exec_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_cmd_suffix_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_cmd_suffix_argument(t_ast_node *curr, char **argv);
void	add_argument(char **argv, char *arg);
int		exec_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx);

// exec_subshell.c
int		exec_redirect_list(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_subshell(t_ast_node *curr, t_shell_ctx *shell_ctx);

// exec_io_here.c
int		exec_io_here(t_ast_node *node, t_shell_ctx *shell_ctx);
int		setup_here_doc(t_ast_node *node, t_shell_ctx *shell_ctx, char **file_name);
int		here_doc_redirect_stdin(int fd, char *file_name);
int		is_there_next_io_here(t_ast_node *curr);
int		free_file_name(char *file_name);

// open_here_doc_tempfile.c
int		open_here_doc_tempfile(char **file_name, char *envp[]);
int		create_unique_file(char **file_name, char *home_path);

// io_readline.c
int		io_readline(int fd, const char *str, t_shell_ctx *shell_ctx);
void	remove_new_line_from_line(char **line);

// exec_io_file.c
int		exec_io_file(t_ast_node *node);
int		exec_io_file_redirect(t_ast_node *node);

// ft_execvpe.c
int		ft_execvpe(const char *file, char *const argv[], char *envp[]);
// ft_getenv.c
char	*ft_getenv(const char *key, char *envp[]);

#endif
