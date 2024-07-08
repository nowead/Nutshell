/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 22:45:42 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse(const char	*input, int *incomplete_cmd, t_shell_ctx *shell_ctx)
{
	t_tokenlist			*tokenlist;
	t_ast				*ast;
	t_ast_err			err;

	tokenlist = tokenize(input, incomplete_cmd);
	if (tokenlist == NULL)
		return (NULL);
	if (expand_parameter(tokenlist, shell_ctx))
		return (clear_tokenlist(tokenlist));
	err = (t_ast_err){};
	ast = program(tokenlist, &err);
	if (err.errnum == INCOMPLETE_CMD)
		*incomplete_cmd = 1;
	else if (err.errnum == ENOMEM)
	{
		errno = err.errnum;
		perror("ENOMEM");
	}
	else if (err.token != NULL)
		ft_dprintf(2, "syntax error near unexpected token \'%s\'\n", \
		get_token_type_string(err.token->type));
	if (ast == NULL)
		clear_tokenlist(tokenlist);
	return (ast);
}

void	set_next_token(t_toknode **toknode)
{
	(*toknode) = (*toknode)->next;
}

t_tokentype	curr_tokentype(t_toknode **toknode)
{
	if (*toknode == NULL || (*toknode)->token == NULL)
		return (TOK_UNKNOWN);
	return ((*toknode)->token->type);
}

t_token	*curr_token(t_toknode **toknode)
{
	if (*toknode == NULL)
		return (NULL);
	return ((*toknode)->token);
}

int	is_ast_err(t_ast_err *err)
{
	if (err->token == NULL && err->errnum == 0)
		return (0);
	return (1);
}

t_ast	*program(t_tokenlist *tokenlist, t_ast_err *err)
{
	t_toknode	*toknode;
	t_ast		*ast;
	t_ast_node	*root;

	if (tokenlist == NULL)
		return (NULL);
	toknode = tokenlist->head;
	root = new_ast_node(0, AND_OR, NULL);
	if (root == NULL)
		return (NULL);
	if (and_or(&toknode, root, err) && \
	curr_tokentype(&toknode) == TOK_NEWLINE)
	{
		ast = (t_ast *)malloc(sizeof(t_ast));
		if (ast == NULL)
			return (NULL);
		ast->root = root;
		ast->tokenlist = tokenlist;
		return (ast);
	}
	if (!is_ast_err(err) && \
	curr_tokentype(&toknode) != TOK_NEWLINE)
		err->token = curr_token(&toknode);
	clear_ast_tree(root);
	return (NULL);
}

int	and_or(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL), err, 2))
		return (0);
	if (pipe_sequence(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, AND_OR_, NULL), err, 2))
			return (0);
		if (and_or_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	and_or_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_AND_IF || \
	curr_tokentype(toknode) == TOK_OR_IF)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		if (curr_tokentype(toknode) == TOK_NEWLINE)
		{
			err->errnum = INCOMPLETE_CMD;
			return (0);
		}
		if (add_ast_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL), err, 2))
			return (0);
		if (pipe_sequence(toknode, curr->child[0], err))
		{
			if (add_ast_child(curr, new_ast_node(1, AND_OR_, NULL), err, 2))
				return (0);
			if (and_or_(toknode, curr->child[1], err))
				return (1);
		}
		err->token = curr_token(toknode);
		return (0);
	}
	return (1);
}

int	pipe_sequence(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, COMMAND, NULL), err, 2))
		return (0);
	if (command(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, PIPE_SEQUENCE_, NULL), err, 2))
			return (0);
		if (pipe_sequence_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	pipe_sequence_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_PIPE)
	{
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(0, COMMAND, NULL), err, 2))
			return (0);
		if (command(toknode, curr->child[0], err))
		{
			if (add_ast_child(curr, \
			new_ast_node(1, PIPE_SEQUENCE_, NULL), err, 2))
				return (0);
			if (pipe_sequence_(toknode, curr->child[1], err))
				return (1);
		}
		if (curr_tokentype(toknode) == TOK_NEWLINE)
			err->errnum = INCOMPLETE_CMD;
		else
			err->token = curr_token(toknode);
		return (0);
	}
	return (1);
}

int	command(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, SIMPLE_COMMAND, NULL), err, 2))
		return (0);
	if (simple_command(toknode, curr->child[0], err))
		return (1);
	else if (!is_ast_err(err))
	{
		clear_ast_tree(curr->child[0]);
		if (add_ast_child(curr, new_ast_node(0, SUBSHELL, NULL), err, 2))
			return (0);
		if (subshell(toknode, curr->child[0], err))
		{
			if (add_ast_child(curr, \
			new_ast_node(1, REDIRECT_LIST, NULL), err, 2))
				return (0);
			if (redirect_list(toknode, curr->child[1], err))
				return (1);
		}
	}
	return (0);
}

int	subshell(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_LPAREN)
	{
		set_next_token(toknode);
		if (curr_tokentype(toknode) == TOK_NEWLINE)
		{
			err->errnum = INCOMPLETE_CMD;
			return (0);
		}
		if (add_ast_child(curr, new_ast_node(0, AND_OR, NULL), err, 1))
			return (0);
		if (and_or(toknode, curr->child[0], err))
		{
			if (curr_tokentype(toknode) == TOK_RPAREN)
			{
				set_next_token(toknode);
				return (1);
			}
		}
		err->token = curr_token(toknode);
	}
	return (0);
}

int	simple_command(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, CMD_PREFIX, NULL), err, 3))
		return (0);
	if (cmd_prefix(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_TOK_WORD, NULL), err, 3))
			return (0);
		if (cmd_word(toknode, curr->child[1]))
		{
			if (add_ast_child(curr, new_ast_node(2, CMD_SUFFIX, NULL), err, 3))
				return (0);
			if (cmd_suffix(toknode, curr->child[2], err))
				return (1);
			err->token = curr_token(toknode);
			return (0);
		}
		clear_ast_tree(curr->child[1]);
		return (1);
	}
	else if (!is_ast_err(err))
		return (simple_command_(toknode, curr, err));
	return (0);
}

int	simple_command_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	clear_ast_tree(curr->child[0]);
	if (add_ast_child(curr, new_ast_node(0, CMD_NAME, NULL), err, 3))
		return (0);
	if (cmd_name(toknode, curr->child[0]))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL), err, 3))
			return (0);
		if (cmd_suffix(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	clear_ast_tree(curr->child[0]);
	return (0);
}

int	cmd_name(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		if (is_assignment_word_token(curr_token(toknode)))
			curr_token(toknode)->type = TOK_ASSIGNMENT_WORD;
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}

int	cmd_word(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		if (is_assignment_word_token(curr_token(toknode)))
			curr_token(toknode)->type = TOK_ASSIGNMENT_WORD;
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}

int	cmd_prefix(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL), err, 2))
		return (0);
	if (io_redirect(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL), err, 2))
			return (0);
		if (cmd_prefix_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	else if (!is_ast_err(err) && is_assignment_word_token(curr_token(toknode)))
	{
		curr_token(toknode)->type = TOK_ASSIGNMENT_WORD;
		clear_ast_tree(curr->child[0]);
		if (add_ast_child(curr, \
		new_ast_node(0, TERMINAL, curr_token(toknode)), err, 2))
			return (0);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(1, CMD_PREFIX_, NULL), err, 2))
			return (0);
		if (cmd_prefix_(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	cmd_prefix_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (cmd_prefix(toknode, curr, err))
		return (1);
	if (is_ast_err(err))
		return (0);
	clear_ast_tree(curr->child[0]);
	return (1);
}

int	cmd_suffix(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		if (add_ast_child(curr, \
		new_ast_node(0, TERMINAL, curr_token(toknode)), err, 2))
			return (0);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL), err, 2))
			return (0);
		if (cmd_suffix(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	else
		return (cmd_suffix_(toknode, curr, err));
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	cmd_suffix_(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL), err, 2))
		return (0);
	if (io_redirect(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, CMD_SUFFIX, NULL), err, 2))
			return (0);
		if (cmd_suffix(toknode, curr->child[1], err))
			return (1);
		err->token = curr_token(toknode);
	}
	clear_ast_tree(curr->child[0]);
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	redirect_list(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_REDIRECT, NULL), err, 2))
		return (0);
	if (io_redirect(toknode, curr->child[0], err))
	{
		if (add_ast_child(curr, new_ast_node(1, REDIRECT_LIST, NULL), err, 2))
			return (0);
		return (redirect_list(toknode, curr->child[1], err));
	}
	clear_ast_tree(curr->child[0]);
	if (is_ast_err(err))
		return (0);
	return (1);
}

int	io_redirect(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (add_ast_child(curr, new_ast_node(0, IO_FILE, NULL), err, 1))
		return (0);
	if (io_file(toknode, curr->child[0], err))
		return (1);
	if (is_ast_err(err))
		return (0);
	clear_ast_tree(curr->child[0]);
	if (add_ast_child(curr, new_ast_node(0, IO_HERE, NULL), err, 1))
		return (0);
	if (io_here(toknode, curr->child[0], err))
		return (1);
	clear_ast_tree(curr->child[0]);
	return (0);
}

int	io_file(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_LESS || \
	curr_tokentype(toknode) == TOK_GREAT || \
	curr_tokentype(toknode) == TOK_DGREAT)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(0, FILENAME, NULL), err, 1))
			return (0);
		if (filename(toknode, curr->child[0]))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	filename(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}

int	io_here(t_toknode **toknode, t_ast_node *curr, t_ast_err *err)
{
	if (curr_tokentype(toknode) == TOK_DLESS)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		if (add_ast_child(curr, new_ast_node(0, HERE_END, NULL), err, 1))
			return (0);
		if (here_end(toknode, curr->child[0]))
			return (1);
		err->token = curr_token(toknode);
	}
	return (0);
}

int	here_end(t_toknode **toknode, t_ast_node *curr)
{
	if (curr_tokentype(toknode) == TOK_WORD)
	{
		curr->token = curr_token(toknode);
		set_next_token(toknode);
		return (1);
	}
	return (0);
}
