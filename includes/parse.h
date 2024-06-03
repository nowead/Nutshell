/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:02:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/03 18:57:15 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"

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
	CMD_WORD,
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

typedef struct s_ast_err
{
	t_token	*token;
	int		errnum;
}	t_ast_err;

// parse.c
t_ast		*parse(const char *input);

void		set_next_token(t_tokenlist_node **tokenlist_node);
t_tokentype	curr_tokentype(t_tokenlist_node **tokenlist_node);
t_token		*curr_token(t_tokenlist_node **tokenlist_node);
int			is_ast_err(t_ast_err *err);

t_ast		*program(t_tokenlist *tokenlist, t_ast_err *err);

int			and_or(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			and_or_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			pipe_sequence(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			pipe_sequence_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			subshell(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			simple_command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			simple_command_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			cmd_name(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			cmd_word(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			cmd_prefix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			cmd_prefix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			cmd_suffix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			cmd_suffix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			redirect_list(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			io_redirect(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			io_file(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			filename(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			io_here(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int			here_end(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);

//print_ast.c
void		print_ast(t_ast_node *node, int depth);
const char *get_token_type_string(t_tokentype type);
const char *get_symbol_type_string(t_symbol sym);

// parsetree.c
t_ast_node	*new_ast_node(int sibling_index, t_symbol sym, t_token *token, size_t child_num);
int			add_ast_child(t_ast_node *node, t_ast_node *child, t_ast_err *err);
void		free_ast_node(t_ast_node *node);
void		clear_ast(t_ast_node *node);


#endif
