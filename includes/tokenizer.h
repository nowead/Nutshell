/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:17:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 17:09:37 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <termios.h>

typedef enum e_tokentype
{
	TOK_UNKNOWN,
	TOK_WORD,
	TOK_ASSIGNMENT_WORD,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_PIPE,
	TOK_LESS,
	TOK_GREAT,
	TOK_DLESS,
	TOK_DGREAT,
	TOK_NEWLINE
}	t_tokentype;

typedef enum e_quotetype
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	MERGED_QUOTE
}	t_quotetype;

typedef struct s_token
{
	t_tokentype		type;
	t_quotetype		quote;
	char			*str;
	int				*is_quoted;
}	t_token;

typedef struct s_toknode
{
	t_token				*token;
	struct s_toknode	*prev;
	struct s_toknode	*next;
}	t_toknode;

typedef struct s_tokenlist
{
	size_t		size;
	t_toknode	*head;
	t_toknode	*back;
}	t_tokenlist;

typedef struct s_tok_handler_args
{
	const char	*input;
	size_t		*tok_start;
	t_tokentype	*tokentype;
	t_quotetype	*quotetype;
	t_tokenlist	*tokenlist;
}	t_token_handler_args;

typedef struct s_ast_err
{
	t_token	*token;
	int		errnum;
}	t_ast_err;

typedef struct s_shell_ctx
{
	char			**envp;
	int				exit_status;
	struct termios	old_term;
	int				stdfd[2];
	char			**heredoc_files;
	size_t			heredoc_idx;
}	t_shell_ctx;

// tokenize.c
t_tokenlist	*tokenize(const char *input, t_ast_err *err, t_shell_ctx *shell_ctx);
int			process_tokens(const char *input, t_tokenlist *tokenlist, \
t_ast_err *err, t_shell_ctx *shell_ctx);
int			add_final_token(t_token_handler_args *args, size_t i);

// token_creation_handler.c
int			handle_token_creation(t_token_handler_args *args, size_t *i);
int			handle_space(t_token_handler_args *args, size_t i);
int			handle_word(t_token_handler_args *args, size_t i);
void		handle_quote(t_token_handler_args *args, size_t i);

// operator_token_creation_handler.c
int			handle_operator(t_token_handler_args *args, size_t i);
int			handle_word_to_operator(t_token_handler_args *args, size_t i);
int			handle_and_if_operator(t_token_handler_args *args, size_t *i);

// operator_token_classification.c
int			is_operator(char c);
int			is_part_of_operator(const char *input, size_t tok_start, size_t i);
t_tokentype	classify_single_operator(char c);
t_tokentype	classify_compound_operator(const char *input, \
size_t tok_start, size_t i);

// token_creation.c
t_tokenlist	*new_tokenlist(void);
t_token		*new_word_token(char *str);
t_token		*new_operator_token(t_tokentype type);
t_toknode	*new_toknode(t_token *token);

// token_addition.c
void		add_toknode(t_tokenlist *tokenlist, t_toknode *toknode);
int			tokenlist_add(t_tokenlist *tokenlist, t_token *token);

// token_free.c
void		free_token(t_token *token);
void		free_toknode(t_toknode *toknode);
void		*clear_tokenlist(t_tokenlist *tokenlist);

// token_removal.c
void		pop_toknode(t_tokenlist *tokenlist, t_toknode *toknode);
void		delete_toknode(t_tokenlist *tokenlist, t_toknode *toknode);

#endif
