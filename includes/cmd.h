/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:05 by damin             #+#    #+#             */
/*   Updated: 2024/06/26 16:18:25 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stdio.h>
# include <stdlib.h>

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

// exec_cmd.c
void	err_ctrl(char *err, int sys, int exit_status);
void    exec_ast(t_ast *ast, char ***envp);
int     exec_and_or(t_ast_node *root, char ***envp);
int     exec_and_or_(t_ast_node *curr, int prev_result, char ***envp);
int     exec_pipe_sequence(t_ast_node *curr, char ***envp);
int     single_command(t_ast_node *curr, char ***envp);
int     multiple_command(t_ast_node *curr, char ***envp);
int     is_there_pipe(t_ast_node *curr);
int     first_command(t_ast_node *curr, int fd[3], char ***envp);
int     middle_command(t_ast_node *curr, int fd[3], char ***envp);
int     last_command(t_ast_node *curr, int fd[3], char ***envp);
void    exec_command(t_ast_node *curr, char ***envp);
void    exec_redirect_list(t_ast_node *curr);
void    exec_subshell(t_ast_node *curr, char ***envp);
int     option_num(t_ast_node *curr);
void    exec_simple_command(t_ast_node *curr, char ***envp);
void    exec_cmd_prefix(t_ast_node *curr, char ***envp);
void    add_argument(char **argv, char *option);
void    exec_cmd_suffix(t_ast_node *curr, char **argv);
void    exec_io_redirect(t_ast_node *curr);
void    exec_assignment_word(t_ast_node *curr, char ***envp);

#endif
