/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:28:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/13 21:25:52 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>

// is_builtin_cmd.c
int		is_builtin_cmd(t_ast_node *curr);

// exec_builtin_command.c
int		exec_builtin_simple_command(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		execute_builtin_argv(char *cmd_name, char **argv, \
t_shell_ctx *shell_ctx);
int		backup_stdin(t_shell_ctx *shell_ctx);
int		restore_stdin(t_shell_ctx *shell_ctx);

// exec_builtin_affixes.c
void	exec_builtin_cmd_prefix(t_ast_node *curr, t_shell_ctx *shell_ctx);
//int		exec_builtin_cmd_suffix(t_ast_node *curr, char **argv, \
//t_shell_ctx *shell_ctx);
void	exec_builtin_io_redirect(t_ast_node *curr, t_shell_ctx *shell_ctx);
void	exec_redirect_in_suffix(t_ast_node *curr, t_shell_ctx *shell_ctx);
int		exec_suffix_without_redirect(t_ast_node *curr, char **argv, \
t_shell_ctx *shell_ctx);


// exec_builtin_io.c
void	exec_builtin_io_here(t_ast_node *node, t_shell_ctx *shell_ctx);
void	exec_builtin_io_file(t_ast_node *node);

// cd.c
int		exec_cd(char **argv, char ***envp);
int		update_oldpwd(char ***envp);
int		update_pwd(char ***envp);
int		cd_home(char **argv, char **envp);
void	exec_cd_in_process(char **argv, char ***envp);

// echo.c
void	exec_echo(char **argv);

// env.c
void	exec_env(t_shell_ctx *shell_ctx);

// exit.c
void	exec_exit(char **argv, t_shell_ctx *shell_ctx);
void	exec_exit_in_process(char **argv);

// export.c
int		exec_export(char **argv, char ***envp);
int		export_single_env_var(char *env_var, char ***envp);
size_t	get_key_len(char *env_var);
char	**search_env_var(const char *key, size_t len, char *envp[]);
int		export_new_env_var(char *new_env_var, char ***envp);

// export_in_pipe.c
void	exec_export_in_pipe(char **argv);

// pwd.c
void	exec_pwd(void);

// unset.c
int		exec_unset(char **argv, char ***envp);
int		unset_single_env_var(char *env_key, char ***envp);
void	exec_unset_in_process(char **argv, char ***envp);

#endif
