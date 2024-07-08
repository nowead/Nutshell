/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:28:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 16:37:27 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>

// handle_built_in.c
int		err_return(char *err_msg);
int		is_builtin_cmd(t_ast_node *curr);
int		exec_builtin_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		execute_builtin_argv(char *cmd_name, char **argv, \
t_shell_ctx *shell_ctx);
int		exec_builtin_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_builtin_cmd_suffix(t_ast_node *curr, char **argv, \
t_shell_ctx *shell_ctx);
int		exec_builtin_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_builtin_io_file(t_ast_node *node);
int		builtin_open_here_doc_tempfile(char **file_name, \
t_shell_ctx *shell_ctx);
int		exec_builtin_io_here(t_ast_node *node, t_shell_ctx *shell_ctx);

// cd.c
int		exec_cd(char **argv, char ***envp);
int		update_oldpwd(char ***envp);
int		update_pwd(char ***envp);
int		cd_home(char **argv, char **envp);

// echo.c
void	exec_echo(char **argv);

// env.c
void	exec_env(t_shell_ctx *shell_ctx);

// exit.c
void	exec_exit(t_shell_ctx *shell_ctx);

// export.c
int		exec_export(char **argv, char ***envp);
int		export_single_env_var(char *env_var, char ***envp);
size_t	get_key_len(char *env_var);
char	**search_env_var(const char *key, size_t len, char *envp[]);
int		export_new_env_var(char *new_env_var, char ***envp);

// pwd.c
void	exec_pwd(void);

// unset.c
int		exec_unset(char **argv, char ***envp);
int		unset_single_env_var(char *env_key, char ***envp);

#endif
