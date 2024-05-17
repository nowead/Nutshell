/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:02:55 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/17 22:47:44 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include "tokenize.h"

typedef enum e_symbol
{
	TERMINAL,
	PROGRAM,
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
	CMD_SUFFIX_,
	REDIRECT_LIST,
	REDIRECT_LIST_,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END
}	t_symbol;

typedef struct s_parsetree_node
{
	t_symbol				sym;
	t_token					*token;
	struct s_parsetree_node	*parent;
	struct s_parsetree_node	*left;
	struct s_parsetree_node	*right;
}	t_parsetree_node;

#endif
