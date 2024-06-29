/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:05 by damin             #+#    #+#             */
/*   Updated: 2024/06/29 21:28:14 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <interface.h>

# ifdef USE_SIGNAL
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# endif

# ifdef USE_READLINE
# include <readline/readline.h>
# include <readline/history.h>
# endif

// io.c
int     exec_io_here(t_ast_node *node);
int     exec_io_file(t_ast_node *node);
int		get_valid_fd(void);
void	io_readline(int fd, const char *str);

// exec_cmd.c
void	err_ctrl(char *err, int sys, int exit_status);
void    exec_ast(t_ast *ast, t_shell_context *shell_ctx);
int     exec_and_or(t_ast_node *root, t_shell_context *shell_ctx);
int     exec_and_or_(t_ast_node *curr, int prev_result, t_shell_context *shell_ctx);
int     exec_pipe_sequence(t_ast_node *curr, t_shell_context *shell_ctx);
int     single_command(t_ast_node *curr, t_shell_context *shell_ctx);
int		exec_external_cmd(t_ast_node *curr, t_shell_context *shell_ctx);
int     multiple_command(t_ast_node *curr, t_shell_context *shell_ctx);
int     is_there_pipe(t_ast_node *curr);
int     first_command(t_ast_node *curr, int fd[3], t_shell_context *shell_ctx);
int     middle_command(t_ast_node *curr, int fd[3], t_shell_context *shell_ctx);
int     last_command(t_ast_node *curr, int fd[3], t_shell_context *shell_ctx);
void    exec_command(t_ast_node *curr, t_shell_context *shell_ctx);
void    exec_redirect_list(t_ast_node *curr);
void    exec_subshell(t_ast_node *curr, t_shell_context *shell_ctx);
int     count_argument(t_ast_node *curr);
void    exec_simple_command(t_ast_node *curr, t_shell_context *shell_ctx);
void    exec_cmd_prefix(t_ast_node *curr, t_shell_context *shell_ctx);
void    add_argument(char **argv, char *option);
void    exec_cmd_suffix(t_ast_node *curr, char **argv);
void    exec_io_redirect(t_ast_node *curr);
size_t	ft_strslen(char **strs);

// built_in_cmd1.c
void    exec_echo(char **argv);
void    exec_exit(t_shell_context *shell_ctx);
int     exec_pwd(void);
int     exec_cd(char *path);
void	exec_env(t_shell_context *shell_ctx);
int		exec_export(char **argv, char ***envp);


// handle_built_in.c
int     err_return(char *err_msg);
int     is_builtin_cmd(t_ast_node *curr);
int		exec_builtin_simple_command(t_ast_node *curr, t_shell_context *shell_ctx);
int		execute_builtin_argv(char *cmd_name, char **argv, t_shell_context *shell_ctx);
int		exec_builtin_cmd_prefix(t_ast_node *curr, t_shell_context *shell_ctx);
int		exec_builtin_cmd_suffix(t_ast_node *curr, char **argv);
int		exec_builtin_io_redirect(t_ast_node *curr);
int		exec_builtin_assignment_word(t_ast_node *curr, t_shell_context *shell_ctx);
int 	exec_builtin_io_file(t_ast_node *node);
int	    exec_builtin_io_here(t_ast_node *node);
#endif
