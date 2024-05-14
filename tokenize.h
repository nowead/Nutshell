/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:17:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/14 20:50:07 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>

// Defines various token types that can be recognized.
typedef enum e_tokentype
{
	TOK_UNKNOWN,
	TOK_WORD,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_PIPE,
	TOK_LESS,
	TOK_GREAT,
	TOK_DLESS,
	TOK_DGREAT
}	t_tokentype;

// Defines the types of quotations that can be recognized.
typedef enum e_quotetype
{
	NO_QUOTE,				// No quotation
	SINGLE_QUOTE,			// Enclosed in single quotes
	DOUBLE_QUOTE			// Enclosed in double quotes
}	t_quotetype;

// Represents a single token.
typedef struct s_token
{
	t_tokentype		type;	// Type of token
	char			*str;	// String value of token
	struct s_token	*prev;	// Pointer to previous token in the list
	struct s_token	*next;	// Pointer to next token in the list
}	t_token;

// Represents a list of tokens.
typedef struct s_tokenlist
{
	size_t	size;			// Number of tokens in the list
	t_token	*head;			// Pointer to the first token in the list
	t_token	*back;			// Pointer to the last token in the list
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

// Function declarations for tokenizer operations.
// tokenize.c
t_tokenlist	*tokenize(const char *input); // Tokenizes the given input string
void		process_tokens(const char *input, t_tokenlist *tokenlist); // Processes input to generate tokens
void		add_final_token(t_token_handler_args *args, size_t i); // Handles the creation of the final token
void		tokenize_err_exit(t_tokenlist *tokenlist, char *err_msg); // Handles errors by cleaning up and exiting
// debugging functions
char		*tokentype_to_str(t_tokentype tokentype); // Converts tokentype to corresponding string
int			print_tokenlist(t_tokenlist *tokenlist); // Prints all tokens in the list for debugging

// tokenlist.c
t_tokenlist	*new_tokenlist(void); // Creates a new token list
t_token		*new_word_token(char *str); // Creates a new word token
t_token		*new_operator_token(t_tokentype type); // Creates a new operator token
int			tokenlist_add(t_tokenlist *tokenlist, t_token *token); // Adds a token to the list
void		tokenlist_clear(t_tokenlist *tokenlist); // Clears the token list, freeing all resources

// tokenize_handle_token.c
void		handle_token_creation(t_token_handler_args *args, size_t *i); // Handles creation of a single token
void		handle_operator(t_token_handler_args *args, size_t i); // Handles operator tokens
void		handle_and_if_operator(t_token_handler_args *args, size_t *i);
void		handle_space(t_token_handler_args *args, size_t i); // Handles spaces and separates tokens
void		handle_word(t_token_handler_args *args, size_t i); // Handles word tokens

// tokenize_classify_operator.c
int			is_operator(char c);  // Checks if a character is an operator
int			is_part_of_operator(const char *input, size_t tok_start, size_t i); // Checks if a sequence forms an operator
t_tokentype	classify_single_operator(char c); // Classifies a single character operator
t_tokentype	classify_compound_operator(const char *input, \
size_t tok_start, size_t i); // Classifies a compound operator

#endif
