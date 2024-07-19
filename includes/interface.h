/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:11:21 by damin             #+#    #+#             */
/*   Updated: 2024/07/19 13:56:44 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_H
# define INTERFACE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"

# define ECHOCTL_ON 1
# define ECHOCTL_OFF 0

typedef enum e_symbol
{
	TERMINAL,
	AND_OR,
	AND_OR_,
	PIPE_SEQUENCE,
	PIPE_SEQUENCE_,
	COMMAND,
	SUBSHELL,
	SIMPLE_COMMAND,
	CMD_NAME,
	CMD_TOK_WORD,
	CMD_PREFIX,
	CMD_PREFIX_,
	CMD_SUFFIX,
	REDIRECT_LIST,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END
}	t_symbol;

typedef struct s_ast_node
{
	int					sibling_index;
	t_symbol			sym;
	t_token				*token;
	struct s_ast_node	*parent;
	struct s_ast_node	**child;
	size_t				child_num;
}	t_ast_node;

typedef struct s_ast
{
	t_ast_node	*root;
	t_tokenlist	*tokenlist;
}	t_ast;

// interface.c
int			run_shell(char *envp[]);
void		shell_main_loop(t_shell_ctx *shell_ctx);
void		execute_parsed_command(t_ast *ast, t_shell_ctx *shell_ctx, \
char *line);
int			clear_here_doc_files(t_shell_ctx *shell_ctx);

// echo_control.c
void		set_echoctl(struct termios *old_term, int echoctl_flag, \
int stdin_fd);
void		restore_echoctl(struct termios *old_term, int stdin_fd);

// signal_handler.c
void		init_signal_handler(void);
void		sigint_handler(int signo);
void		here_doc_handler(int signo);
void		convert_to_child_process(void);
void		convert_to_nutshell_terminal(void);

// init_shell_context.c
void		init_shell_ctx(t_shell_ctx *shell_ctx, char **envp);
char		**init_envp(char *envp[]);

// handle_input.c
int			handle_input(t_shell_ctx *shell_ctx, char **line);
void		exit_shell(t_shell_ctx *shell_ctx);

// backup_stdfd.c
int			backup_stdfd(t_shell_ctx *shell_ctx);
int			restore_stdfd(t_shell_ctx *shell_ctx);

#endif
