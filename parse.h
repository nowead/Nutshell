/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:02:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/22 14:38:36 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include "tokenize.h"

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

// parsetree.c
t_ast_node	*new_ast_node(int sibling_index, t_symbol sym, t_token *token, size_t child_num);
void		add_ast_node_child(t_ast_node *node, t_ast_node *child);
void		free_ast_node(t_ast_node *node);
void		clear_ast(t_ast_node *node);

#endif
