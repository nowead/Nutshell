/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:05 by damin             #+#    #+#             */
/*   Updated: 2024/06/12 15:41:25 by damin            ###   ########.fr       */
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

void	err_ctrl(char *err, int sys, int exit_status);

//io.c
void	e_io_here(char *token_str);

//cmd_a.c
int     e_and_or(t_ast_node *node);
int     e_and_or_(t_ast_node *node, int ret_pipe_sequnece);
int     e_pipe_sequence(t_ast_node *node);
int     e_pipe_sequence_(t_ast_node *nodem, int depth);
int     e_cmd(t_ast_node *node, int depth);
int     e_simple_cmd(t_ast_node *node);

void	ctrl_cmd(t_ast *ast);
#endif