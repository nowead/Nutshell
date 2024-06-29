/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:02:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/29 21:28:01 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

#define INCOMPLETE_CMD 1001

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
t_ast				*parse(const char *input, int *incomplete_command, char *envp[]);

void				set_next_token(t_tokenlist_node **tokenlist_node);
t_tokentype			curr_tokentype(t_tokenlist_node **tokenlist_node);
t_token				*curr_token(t_tokenlist_node **tokenlist_node);
int					is_ast_err(t_ast_err *err);

t_ast				*program(t_tokenlist *tokenlist, t_ast_err *err);

int					and_or(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					and_or_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					pipe_sequence(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					pipe_sequence_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					subshell(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					simple_command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					simple_command_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					cmd_name(t_tokenlist_node **tokenlist_node, t_ast_node *curr);
int					cmd_word(t_tokenlist_node **tokenlist_node, t_ast_node *curr);
int					cmd_prefix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					cmd_prefix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					cmd_suffix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					cmd_suffix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					redirect_list(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					io_redirect(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					io_file(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					filename(t_tokenlist_node **tokenlist_node, t_ast_node *curr);
int					io_here(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err);
int					here_end(t_tokenlist_node **tokenlist_node, t_ast_node *curr);

//print_ast.c
void				print_ast(t_ast_node *node, int depth);
const char			 *get_token_type_string(t_tokentype type);
const char			 *get_symbol_type_string(t_symbol sym);

// parsetree.c
t_ast_node			*new_ast_node(int sibling_index, t_symbol sym, t_token *token);
int					add_ast_child(t_ast_node *node, t_ast_node *child, t_ast_err *err, size_t max_child_num);
void				free_ast_node(t_ast_node *node);
void				clear_ast_tree(t_ast_node *node);
void				clear_ast(t_ast	*ast);

//is_assignment_word.c
int					is_assignment_word_token(t_token *token);
int					is_assignment_word(char *str);

//split_quotes.c
t_tokenlist			*split_into_subtokens(t_tokenlist_node *tokenlist_node);

// expand_parameter.c
int					expand_parameter(t_tokenlist *tokenlist, char *envp[]);
int					expand_parameters_in_a_token(t_tokenlist_node *tokenlist_node, t_tokenlist *tokenlist, char *envp[]);
t_tokenlist			*split_subtokens_into_fields(t_tokenlist *subtokenlist);
int					handle_no_quote_token(t_tokenlist_node **curr_subtok, t_tokenlist *fields);
int					handle_first_field(char *str, size_t *i, t_tokenlist *fields);
int					handle_middle_field(char *str, size_t *i, t_tokenlist *fields, int *is_space);
int					handle_last_field(t_tokenlist *fields, t_tokenlist_node **curr_subtok);
void				handle_quote_token(t_tokenlist *subtokenlist, t_tokenlist_node **curr_subtok, t_tokenlist *fields);
t_token				*merge_two_tokens(t_token *token1, t_token *token2);
t_token				*get_field(char *str, size_t *i);
void				insert_fields_into_tokenlist(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node, t_tokenlist *fields);

// split_into_subtokens.c
t_tokenlist			*split_into_subtokens(t_tokenlist_node *tokenlist_node);

// expand_subtokenlist.c
int					expand_parameters_in_subtokens(t_tokenlist *subtokenlist, char *envp[]);

// ft_execvpe.c
int					ft_execvpe(const char *file, char *const argv[], char *envp[]);
// ft_getenv.c
char				*ft_getenv(const char *key, char *envp[]);

#endif
