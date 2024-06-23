/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:17:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/23 17:38:44 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>

typedef enum e_tokentype
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
	DOUBLE_QUOTE
}	t_quotetype;

typedef struct s_token
{
	t_tokentype		type;
	t_quotetype		quote;
	char			*str;
}	t_token;

typedef struct s_tokenlist_node
{
	t_token					*token;
	struct s_tokenlist_node	*prev;
	struct s_tokenlist_node	*next;
}	t_tokenlist_node;

typedef struct s_tokenlist
{
	size_t				size;
	t_tokenlist_node	*head;
	t_tokenlist_node	*back;
}	t_tokenlist;

// Struct to pass arguments for token handling functions.
typedef struct s_token_handler_args
{
	const char	*input;		// Input string being tokenized
	size_t		*tok_start;	// Index where current token starts
	t_tokentype	*tokentype;	// Current token type
	t_quotetype	*quotetype;	// Current quote type
	t_tokenlist	*tokenlist;	// List to store tokens
}	t_token_handler_args;

// tokenize.c
t_tokenlist			*tokenize(const char *input, int *incomplete_cmd); // Tokenizes the given input string
int					process_tokens(const char *input, t_tokenlist *tokenlist, int *incomplete_cmd); // Processes input to generate tokens
int					add_final_token(t_token_handler_args *args, size_t i); // Handles the creation of the final token
// debugging function
int					print_tokenlist(t_tokenlist *tokenlist); // Prints all tokens in the list for debugging

// tokenlist.c
t_tokenlist			*new_tokenlist(void); // Creates a new token list
t_token				*new_word_token(char *str); // Creates a new word token
t_token				*new_operator_token(t_tokentype type); // Creates a new operator token
t_tokenlist_node	*new_tokenlist_node(t_token *token); // Creates a node of the list of tokens
void				tokenlist_add_node(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node);
int					tokenlist_add(t_tokenlist *tokenlist, t_token *token); // Adds a token to the list
void				free_token(t_token *token); // Frees a token
void				free_tokenlist_node(t_tokenlist_node *tokenlist_node); // Frees a node of the tokenlist
void				*clear_tokenlist(t_tokenlist *tokenlist); // Clears the token list, freeing all resources
void				pop_tokenlist_node(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node);
void				delete_tokenlist_node(t_tokenlist *tokenlist, t_tokenlist_node *tokenlist_node);

// tokenize_handle_token.c
int					handle_token_creation(t_token_handler_args *args, size_t *i); // Handles creation of a single token
int					handle_operator(t_token_handler_args *args, size_t i); // Handles operator tokens
int					handle_and_if_operator(t_token_handler_args *args, size_t *i);
int					handle_space(t_token_handler_args *args, size_t i); // Handles spaces and separates tokens
int					handle_word(t_token_handler_args *args, size_t i); // Handles word tokens

// tokenize_classify_operator.c
int					is_operator(char c);  // Checks if a character is an operator
int					is_part_of_operator(const char *input, size_t tok_start, size_t i); // Checks if a sequence forms an operator
t_tokentype			classify_single_operator(char c); // Classifies a single character operator
t_tokentype			classify_compound_operator(const char *input, \
size_t tok_start, size_t i); // Classifies a compound operator

#endif
