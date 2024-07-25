/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:02:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/25 21:54:00 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include "interface.h"

# define INCOMPLETE_CMD 1001

// parse.c
t_ast		*parse(const char *input, t_shell_ctx *shell_ctx);
void		handle_parse_error(t_ast_err *err, t_shell_ctx *shell_ctx);
const char	*get_token_type_string(t_tokentype type);
const char	*get_token_operator_type_string(t_tokentype type);
// void		print_ast(t_ast_node *node, int depth);
// const char	*get_symbol_type_string(t_symbol sym);

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
int			expand_parameters_in_simple_command(t_ast_node *curr, \
t_shell_ctx *shell_ctx);
int			expand_parameters_in_cmd_name(t_ast_node *curr, \
t_shell_ctx *shell_ctx);
// unquote_a_token.c
int         unquote_a_token(t_toknode *curr);
size_t      get_unquoted_len(char *str);
void    	copy_str_to_unquoted_str(char *unquoted_str, char *str);
void    	evaluate_quotetype(const char *str, const size_t i, t_quotetype *quotetype);
int         is_real_quote(const char *str, const size_t i, const t_quotetype quotetype);
// expand_parameters_in_a_token.c
t_tokenlist *expand_parameters_in_a_token(t_token *token, \
t_shell_ctx *shell_ctx);
t_tokenlist	*split_into_subtokens_and_expand(t_token *token, \
t_shell_ctx *shell_ctx);
t_tokenlist	*save_quote_and_split_into_fields(t_tokenlist *subtokenlist);
t_tokenlist	*expand_pathname_and_split_fields(t_tokenlist *fields);

// expand_parameters_in_string.c
int			expand_parameters_in_string(char **str, t_shell_ctx *shell_ctx);
int			expand_single_parameter(char **str, size_t *i, \
t_shell_ctx *shell_ctx);
void		search_env_end(char *str, size_t *i);
char		*get_env_value(char *str, size_t start, size_t i, char *envp[]);
// expand_parameters_in_subtokens.c
int			expand_parameters_in_subtokens(t_tokenlist *subtokenlist, \
t_shell_ctx *shell_ctx);
int			expand_parameters_in_a_subtoken(t_toknode *subtoknode, \
t_shell_ctx *shell_ctx);
// is_assignment_word.c
int			is_assignment_word_token(t_token *token);
int			is_assignment_word(char *str);
int			is_export_word(char *str);
int			is_valid_name(const char *str, size_t len);
// split_into_subtokens.c
t_tokenlist	*split_into_subtokens(t_token *token);
// save_quote_in_subtokens.c
int			save_quote_in_subtokens(t_tokenlist *subtokenlist);
int			save_quote_in_a_token(t_toknode *toknode);
void		fill_int_array(int *arr, size_t len, int value);
// split_subtokens_into_fields.c
t_tokenlist	*split_subtokens_into_fields(t_tokenlist *subtokenlist);
int			handle_quote_token(t_tokenlist *subtokenlist, \
t_toknode **curr_subtok, t_tokenlist *fields);
t_token		*merge_two_tokens(t_token *token1, t_token *token2);
int			*merge_is_quoted(t_token *token1, t_token *token2);
// split_no_quote_subtoken.c
int			handle_no_quote_token(t_toknode **curr_subtok, t_tokenlist *fields);
int			handle_first_field(char *str, size_t *i, t_tokenlist *fields);
int			handle_middle_field(char *str, size_t *i, \
t_tokenlist *fields, int *is_space);
int			handle_last_field(t_tokenlist *fields, t_toknode **curr_subtok);
t_token		*get_field(char *str, size_t *i);
// expand_pathname.c
int			expand_pathname_in_fields(t_tokenlist *fields);
int			expand_pathname_in_single_field(t_toknode *curr);
void		handle_expanded_pathname_update_token(t_toknode *curr, \
char *exp_str);
size_t		count_asterisk(t_token *token);
int			fill_patterns(char **patterns, t_token *token);
// construct_expanded_pathname.c
char		*construct_expanded_pathname(char **patterns, size_t pattern_cnt);
int			concatenate_space_and_pathname(DIR *dir, struct dirent *entry, \
char **exp_str);
int			does_entry_match_patterns(char *entry, char **patterns, \
size_t pattern_cnt);
int			concatenate_space(char **exp_str);
int			concatenate_pathname(char **exp_str, char *entry);
// sort_expanded_pathname.c
int			sort_expanded_pathname(char **exp_str);
void		ft_string_sort(char **strs, size_t len);
void		ft_swap_strings(char **a, char **b);
char		*ft_strsjoin(char **strs, char c);
size_t		get_joined_len(char **strs);
// split_expanded_fields.c
t_tokenlist	*split_expanded_fields(t_tokenlist *fields);
int			split_single_field(char *str, t_tokenlist *splited_fields);
t_token		*get_splited_field(char *str, size_t *i);

#endif
