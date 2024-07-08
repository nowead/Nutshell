/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:02:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 17:28:04 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "interface.h"

# define INCOMPLETE_CMD 1001

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
t_ast				*parse(const char *input, int *incomplete_command, \
t_shell_ctx *shell_ctx);

void				set_next_token(t_toknode **toknode);
t_tokentype			curr_tokentype(t_toknode **toknode);
t_token				*curr_token(t_toknode **toknode);
int					is_ast_err(t_ast_err *err);

t_ast				*program(t_tokenlist *tokenlist, t_ast_err *err);

int					and_or(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					and_or_(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					pipe_sequence(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					pipe_sequence_(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					command(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					subshell(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					simple_command(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					simple_command_(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					cmd_name(t_toknode **toknode, t_ast_node *curr);
int					cmd_word(t_toknode **toknode, t_ast_node *curr);
int					cmd_prefix(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					cmd_prefix_(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					cmd_suffix(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					cmd_suffix_(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					redirect_list(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					io_redirect(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					io_file(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					filename(t_toknode **toknode, t_ast_node *curr);
int					io_here(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int					here_end(t_toknode **toknode, t_ast_node *curr);

// get_token_type_string.c
const char			*get_token_type_string(t_tokentype type);
const char			*get_token_operator_type_string(t_tokentype type);
// void				print_ast(t_ast_node *node, int depth);
// const char		*get_symbol_type_string(t_symbol sym);

// parsetree.c
t_ast_node			*new_ast_node(int sibling_index, t_symbol sym, \
t_token *token);
int					add_ast_child(t_ast_node *node, t_ast_node *child, \
t_ast_err *err, size_t max_child_num);
void				free_ast_node(t_ast_node *node);
void				clear_ast_tree(t_ast_node *node);
void				clear_ast(t_ast	*ast);

//is_assignment_word.c
int					is_assignment_word_token(t_token *token);
int					is_assignment_word(char *str);
int					is_valid_name(const char *str, size_t len);

//split_quotes.c
t_tokenlist			*split_into_subtokens(t_toknode *toknode);

// expand_parameter.c
int					expand_parameter(t_tokenlist *tokenlist, \
t_shell_ctx *shell_ctx);
int					expand_parameters_in_a_token(t_toknode *toknode, \
t_tokenlist *tokenlist, t_shell_ctx *shell_ctx);
t_tokenlist			*split_subtokens_into_fields(t_tokenlist *subtokenlist);
int					handle_no_quote_token(t_toknode **curr_subtok, \
t_tokenlist *fields);
int					handle_first_field(char *str, size_t *i, \
t_tokenlist *fields);
int					handle_middle_field(char *str, size_t *i, \
t_tokenlist *fields, int *is_space);
int					handle_last_field(t_tokenlist *fields, \
t_toknode **curr_subtok);
void				handle_quote_token(t_tokenlist *subtokenlist, \
t_toknode **curr_subtok, t_tokenlist *fields);
t_token				*merge_two_tokens(t_token *token1, t_token *token2);
t_token				*get_field(char *str, size_t *i);
void				insert_fields_into_tokenlist(t_tokenlist *tokenlist, \
t_toknode *toknode, t_tokenlist *fields);

// split_into_subtokens.c
t_tokenlist			*split_into_subtokens(t_toknode *toknode);

// expand_subtokenlist.c
int					expand_parameters_in_subtokens(t_tokenlist *subtokenlist, \
t_shell_ctx *shell_ctx);

// ft_execvpe.c
int					ft_execvpe(const char *file, char *const argv[], \
char *envp[]);
// ft_getenv.c
char				*ft_getenv(const char *key, char *envp[]);

#endif
