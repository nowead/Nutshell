/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/18 10:56:30 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse(const char* input)
{
	t_tokenlist			*tokenlist;
	t_ast				*ast;
	t_ast_err			err;

	tokenlist = tokenize(input);
	if (expand_parameter(tokenlist))
		return (tokenlist_clear(tokenlist));
	err = (t_ast_err){};
	ast = program(tokenlist, &err);
	if (err.errnum != 0)
	{
		err.token = NULL;
		errno = err.errnum;
		perror("ENOMEM");
	}
	if (err.token != NULL)
		dprintf(2, "syntax error near unexpected token \'%s\'\n", \
		get_token_type_string(err.token->type));
	if (ast == NULL)
		tokenlist_clear(tokenlist);
	return (ast);
}

void	set_next_token(t_tokenlist_node **tokenlist_node)
{
	(*tokenlist_node) = (*tokenlist_node)->next;
}

t_tokentype	curr_tokentype(t_tokenlist_node **tokenlist_node)
{
	if (*tokenlist_node == NULL || (*tokenlist_node)->token == NULL)
		return (UNKNOWN);
	return ((*tokenlist_node)->token->type);
}

t_token	*curr_token(t_tokenlist_node **tokenlist_node)
{
	if (*tokenlist_node == NULL)
		return (NULL);
	return ((*tokenlist_node)->token);
}

int	is_ast_err(t_ast_err *err)
{
	if (err->token == NULL && err->errnum == 0)
		return (0);
	return (1);
}

t_ast	*program(t_tokenlist *tokenlist, t_ast_err *err)
{
	t_tokenlist_node	*tokenlist_node;
	t_ast				*ast;
	t_ast_node			*root;

	if (tokenlist == NULL)
		return (NULL);
	tokenlist_node = tokenlist->head;
	root = new_ast_node(0, AND_OR, NULL, 2);
	if (root == NULL)
		return (NULL);
	if (and_or(&tokenlist_node, root, err) && \
	curr_tokentype(&tokenlist_node) == NEWLINE)
	{
		ast = (t_ast *)malloc(sizeof(t_ast));
		if (ast == NULL)
			return (NULL);
		ast->root = root;
		ast->tokenlist = tokenlist;
		return (ast);
	}
	if (!is_ast_err(err) && \
	curr_tokentype(&tokenlist_node) != NEWLINE)
		err->token = curr_token(&tokenlist_node);
	clear_ast(root);
	return (NULL);
}

int	and_or(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL, 2), err))
		return (0);
	if (pipe_sequence(tokenlist_node, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, AND_OR_, NULL, 2), err))
			return (0);
		if (and_or_(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	return (0);
}

int	and_or_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(tokenlist_node) == AND_IF || \
	curr_tokentype(tokenlist_node) == OR_IF)
	{
		curr->token = curr_token(tokenlist_node);
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL, 2), err))
			return (0);
		if (pipe_sequence(tokenlist_node, curr->child[0], err))
		{
			if (add_ast_child(curr, new_ast_node(1, AND_OR_, NULL, 3), err))
				return (0);
			if (and_or_(tokenlist_node, curr->child[1], err))
				return (1);
		}
		err->token = curr_token(tokenlist_node);
		return (0);
	}
	return (1);
}

int	pipe_sequence(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, COMMAND, NULL, 2), err))
		return (0);
	if (command(tokenlist_node, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, PIPE_SEQUENCE_, NULL, 2), err))
			return (0);
		if (pipe_sequence_(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	return (0);
}

int	pipe_sequence_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(tokenlist_node) == PIPE)
	{
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(0, COMMAND, NULL, 2), err))
			return (0);
		if (command(tokenlist_node, curr->child[0], err))
		{
			if (add_ast_child(curr, \
			new_ast_node(1, PIPE_SEQUENCE_, NULL, 2), err))
				return (0);
			if (pipe_sequence_(tokenlist_node, curr->child[1], err))
				return (1);
		}
		err->token = curr_token(tokenlist_node);
		return (0);
	}
	return (1);
}

int	command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, SIMPLE_COMMAND, NULL, 3), err))
		return (0);
	if (simple_command(tokenlist_node, curr->child[0], err))
		return (1);
	else if (!is_ast_err(err))
	{
		clear_ast(curr->child[0]);
		if (add_ast_child(curr, new_ast_node(0, SUBSHELL, NULL, 1), err))
			return (0);
		if (subshell(tokenlist_node, curr->child[0], err))
		{
			if (add_ast_child(curr, \
			new_ast_node(1, REDIRECT_LIST, NULL, 2), err))
				return (0);
			if (redirect_list(tokenlist_node, curr->child[1], err))
				return (1);
		}
	}
	return (0);
}

int	subshell(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(tokenlist_node) == LPAREN)
	{
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(0, AND_OR, NULL, 2), err))
			return (0);
		if (and_or(tokenlist_node, curr->child[0], err))
		{
			if (curr_tokentype(tokenlist_node) == RPAREN)
			{
				set_next_token(tokenlist_node);
				return (1);
			}
		}
		err->token = curr_token(tokenlist_node);
	}
	return (0);
}

int	simple_command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, CMD_PREFIX, NULL, 2), err))
		return (0);
	if (cmd_prefix(tokenlist_node, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_WORD, NULL, 1), err))
			return (0);
		if (cmd_word(tokenlist_node, curr->child[1]))
		{
			if (add_ast_child(curr, new_ast_node(2, CMD_SUFFIX, NULL, 2), err))
				return (0);
			if (cmd_suffix(tokenlist_node, curr->child[2], err))
				return (1);
			err->token = curr_token(tokenlist_node);
			return (0);
		}
		clear_ast(curr->child[1]);
		return (1);
	}
	else if (!is_ast_err(err))
		return (simple_command_(tokenlist_node, curr, err));
	return (0);
}

int	simple_command_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	clear_ast(curr->child[0]);
	if (add_ast_child(curr, new_ast_node(0, CMD_NAME, NULL, 0), err))
		return (0);
	if (cmd_name(tokenlist_node, curr->child[0]))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL, 2), err))
			return (0);
		if (cmd_suffix(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	clear_ast(curr->child[0]);
	return (0);
}

int	cmd_name(t_tokenlist_node **tokenlist_node, t_ast_node *curr)
{
	if (curr_tokentype(tokenlist_node) == WORD)
	{
		if (is_assignment_word(curr_token(tokenlist_node)))
			curr_token(tokenlist_node)->type = ASSIGNMENT_WORD;
		curr->token = curr_token(tokenlist_node);
		set_next_token(tokenlist_node);
		return (1);
	}
	return (0);
}

int	cmd_word(t_tokenlist_node **tokenlist_node, t_ast_node *curr)
{
	if (curr_tokentype(tokenlist_node) == WORD)
	{
		if (is_assignment_word(curr_token(tokenlist_node)))
			curr_token(tokenlist_node)->type = ASSIGNMENT_WORD;
		curr->token = curr_token(tokenlist_node);
		set_next_token(tokenlist_node);
		return (1);
	}
	return (0);
}

int	cmd_prefix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1), err))
		return (0);
	if (io_redirect(tokenlist_node, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL, 2), err))
			return (0);
		if (cmd_prefix_(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	else if (!is_ast_err(err) && \
	is_assignment_word(curr_token(tokenlist_node)))
	{
		curr_token(tokenlist_node)->type = ASSIGNMENT_WORD;
		clear_ast(curr->child[0]);
		if (add_ast_child(curr, \
		new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 0), err))
			return (0);
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL, 2), err))
			return (0);
		if (cmd_prefix_(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	return (0);
}

int	cmd_prefix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1), err))
		return (0);
	if (io_redirect(tokenlist_node, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL, 2), err))
			return (0);
		if (cmd_prefix_(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	else if (!is_ast_err(err) && \
	is_assignment_word(curr_token(tokenlist_node)))
	{
		curr_token(tokenlist_node)->type = ASSIGNMENT_WORD;
		clear_ast(curr->child[0]);
		if (add_ast_child(curr, new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 0), err))
			return (0);
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL, 2), err))
			return (0);
		if (cmd_prefix_(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	if (is_ast_err(err))
		return (0);
	clear_ast(curr->child[0]);
	return (1);
}

int	cmd_suffix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(tokenlist_node) == WORD)
	{
		if (add_ast_child(curr, \
		new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 0), err))
			return (0);
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL, 2), err))
			return (0);
		if (cmd_suffix(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	else
		return (cmd_suffix_(tokenlist_node, curr, err));
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	cmd_suffix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1), err))
		return (0);
	if (io_redirect(tokenlist_node, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL, 2), err))
			return (0);
		if (cmd_suffix(tokenlist_node, curr->child[1], err))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	clear_ast(curr->child[0]);
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	redirect_list(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1), err))
		return (0);
	if (io_redirect(tokenlist_node, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, REDIRECT_LIST, NULL, 2), err))
			return (0);
		return (redirect_list(tokenlist_node, curr->child[1], err));
	}
	clear_ast(curr->child[0]);
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	io_redirect(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_FILE, NULL, 1), err))
		return (0);
	if (io_file(tokenlist_node, curr->child[0], err))
		return (1);
	if (is_ast_err(err))
		return (0);
	clear_ast(curr->child[0]);
	if (add_ast_child(curr, new_ast_node(0, IO_HERE, NULL, 1), err))
		return (0);
	if (io_here(tokenlist_node, curr->child[0], err))
		return (1);
	clear_ast(curr->child[0]);
	return (0);
}

int	io_file(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(tokenlist_node) == LESS || \
	curr_tokentype(tokenlist_node) == GREAT || \
	curr_tokentype(tokenlist_node) == DGREAT)
	{
		curr->token = curr_token(tokenlist_node);
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(0, FILENAME, NULL, 0), err))
			return (0);
		if (filename(tokenlist_node, curr->child[0]))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	return (0);
}

int	filename(t_tokenlist_node **tokenlist_node, t_ast_node *curr)
{
	if (curr_tokentype(tokenlist_node) == WORD)
	{
		curr->token = curr_token(tokenlist_node);
		set_next_token(tokenlist_node);
		return (1);
	}
	return (0);
}

int	io_here(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(tokenlist_node) == DLESS)
	{
		curr->token = curr_token(tokenlist_node);
		set_next_token(tokenlist_node);
		if (add_ast_child(curr, new_ast_node(0, HERE_END, NULL, 0), err))
			return (0);
		if (here_end(tokenlist_node, curr->child[0]))
			return (1);
		err->token = curr_token(tokenlist_node);
	}
	return (0);
}

int	here_end(t_tokenlist_node **tokenlist_node, t_ast_node *curr)
{
	if (curr_tokentype(tokenlist_node) == WORD)
	{
		curr->token = curr_token(tokenlist_node);
		set_next_token(tokenlist_node);
		return (1);
	}
	return (0);
}
