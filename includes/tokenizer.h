/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:17:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 17:30:05 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>

typedef enum e_toktype
{
	UNKNOWN,
	WORD,
	ASSIGNMENT_WORD,
	LPAREN,
	RPAREN,
	AND_IF,
	OR_IF,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	NEWLINE
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

// tokenize.c
t_tokenlist			*tokenize(const char *input, int *incomplete_cmd);
int					process_toks(const char *input, t_tokenlist *tokenlist, \
int *incomplete_cmd);
int					add_final_token(t_token_handler_args *args, size_t i);

// tokenlist.c
t_tokenlist			*new_tokenlist(void);
t_token				*new_word_token(char *str);
t_token				*new_operator_token(t_tokentype type);
t_toknode			*new_toknode(t_token *token);
void				tokenlist_add_node(t_tokenlist *tokenlist, \
t_toknode *toknode);
int					tokenlist_add(t_tokenlist *tokenlist, t_token *token);
void				free_token(t_token *token);
void				free_toknode(t_toknode *toknode);
void				*clear_tokenlist(t_tokenlist *tokenlist);
void				pop_toknode(t_tokenlist *tokenlist, t_toknode *toknode);
void				delete_toknode(t_tokenlist *tokenlist, t_toknode *toknode);

// tokenize_handle_token.c
int					handle_token_creation(t_token_handler_args *args, \
size_t *i);
int					handle_operator(t_token_handler_args *args, size_t i);
int					handle_and_if_operator(t_token_handler_args *args, \
size_t *i);
int					handle_space(t_token_handler_args *args, size_t i);
int					handle_word(t_token_handler_args *args, size_t i);

// tokenize_classify_operator.c
int					is_operator(char c);
int					is_part_of_operator(const char *input, \
size_t tok_start, size_t i);
t_tokentype			classify_single_operator(char c);
t_tokentype			classify_compound_operator(const char *input, \
size_t tok_start, size_t i);

#endif
