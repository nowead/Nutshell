/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:02:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 20:23:35 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "interface.h"

# define INCOMPLETE_CMD 1001

typedef struct s_ast_err
{
	t_token	*token;
	int		errnum;
}	t_ast_err;

// parse.c
t_ast		*parse(const char *input, int *incomplete_command, \
t_shell_ctx *shell_ctx);
const char	*get_token_type_string(t_tokentype type);
const char	*get_token_operator_type_string(t_tokentype type);
// void				print_ast(t_ast_node *node, int depth);//
// const char		*get_symbol_type_string(t_symbol sym);//

// ast_construction

// and_or.c
int			and_or(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
int			and_or_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
// ast_construction.c
t_ast		*program(t_tokenlist *tokenlist, t_ast_err *err);
// ast_error_handling.c
int			is_ast_err(t_ast_err *err);
// command_name.c
int			cmd_name(t_toknode **toknode, t_ast_node *curr);
int			cmd_word(t_toknode **toknode, t_ast_node *curr);
// command.c
int			command(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
int			simple_command(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int			simple_command_(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
// file_redirections.c
int			io_file(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
int			filename(t_toknode **toknode, t_ast_node *curr);
// here_doc_redirections.c
int			io_here(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
int			here_end(t_toknode **toknode, t_ast_node *curr);
// manage_ast.c
t_ast_node	*new_ast_node(int sibling_index, t_symbol sym, t_token *token);
int			add_ast_child(t_ast_node *node, t_ast_node *child, \
t_ast_err *err, size_t max_child_num);
void		free_ast_node(t_ast_node *node);
void		clear_ast_tree(t_ast_node *node);
void		clear_ast(t_ast	*ast);

// pipe_sequence.c
int			pipe_sequence(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int			pipe_sequence_(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);

// prefix_and_suffix.c
int			cmd_prefix(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
int			cmd_prefix_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
int			cmd_suffix(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);
int			cmd_suffix_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);

// redirection_handling.c
int			redirect_list(t_toknode **toknode, t_ast_node *curr, \
t_ast_err *err);
int			io_redirect(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);

// subshell.c
int			subshell(t_toknode **toknode, t_ast_node *curr, t_ast_err *err);

// token_management.c
void		set_next_token(t_toknode **toknode);
t_tokentype	curr_tokentype(t_toknode **toknode);
t_token		*curr_token(t_toknode **toknode);

// parameter_expansion

// expand_parameter.c
int			expand_parameter(t_tokenlist *tokenlist, t_shell_ctx *shell_ctx);
int			expand_parameters_in_a_token(t_toknode *toknode, \
t_tokenlist *tokenlist, t_shell_ctx *shell_ctx);
// expand_parameters_in_string.c
int			expand_parameters_in_string(char **str, t_shell_ctx *shell_ctx);
int			expand_single_parameter(char **str, size_t *i, \
t_shell_ctx *shell_ctx);
void		search_env_end(char *str, size_t *i);
char		*construct_expanded_str(char *str, size_t start, size_t *i, \
t_shell_ctx *shell_ctx);
char		*get_env_value(char *str, size_t start, size_t i, char *envp[]);
// expand_parameters_in_subtokens.c
int			expand_parameters_in_subtokens(t_tokenlist *subtokenlist, \
t_shell_ctx *shell_ctx);
int			expand_parameters_in_subtoken(t_toknode *subtoknode, \
t_shell_ctx *shell_ctx);
// insert_fields_into_tokenlist.c
void		insert_fields_into_tokenlist(t_tokenlist *tokenlist, \
t_toknode *toknode, t_tokenlist *fields);
// is_assignment_word.c
int			is_assignment_word_token(t_token *token);
int			is_assignment_word(char *str);
int			is_valid_name(const char *str, size_t len);
// split_into_subtokens.c
t_tokenlist	*split_into_subtokens(t_toknode *toknode);
// split_no_quote_subtoken.c
int			handle_no_quote_token(t_toknode **curr_subtok, t_tokenlist *fields);
int			handle_first_field(char *str, size_t *i, t_tokenlist *fields);
int			handle_middle_field(char *str, size_t *i, \
t_tokenlist *fields, int *is_space);
int			handle_last_field(t_tokenlist *fields, t_toknode **curr_subtok);
t_token		*get_field(char *str, size_t *i);
// split_subtokens_into_fields.c
t_tokenlist	*split_subtokens_into_fields(t_tokenlist *subtokenlist);
int			handle_quote_token(t_tokenlist *subtokenlist, \
t_toknode **curr_subtok, t_tokenlist *fields);
t_token		*merge_two_tokens(t_token *token1, t_token *token2);
// unquote_fields.c
int			unquote_fields(t_tokenlist *fields);
int			unquote_single_field(t_toknode *curr);
size_t		get_unquoted_len(char *str);
void		copy_str_to_unquoted_str(char *unquoted_str, char *str);

#endif
