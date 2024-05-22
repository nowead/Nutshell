/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/22 20:29:21 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_ast_node *parse(const char* input)
{
	t_tokenlist			*tokenlist;
	t_tokenlist_node	*tokenlist_node;
	t_ast_node			*root;
	t_token				*err;

	tokenlist = tokenize(input);
	tokenlist_node = tokenlist->head;
	err = NULL;
	root = program(&tokenlist_node, &err);
	if (err != NULL)
		dprintf(2, "syntax error near unexpected token");
	return (root);
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
	return ((*tokenlist_node)->token);
}

int	accept(t_tokentype tokentype, t_tokenlist_node **tokenlist_node)
{
    if (*tokenlist_node != NULL && \
	curr_token(tokenlist_node) != NULL && \
	curr_tokentype(tokenlist_node) == tokentype)
	{
        set_next_token(tokenlist_node);
        return (1);
    }
    return (0);
}

int	expect(t_tokentype tokentype, t_tokenlist_node **tokenlist_node, t_token **err)
{
    if (accept(tokentype, tokenlist_node))
        return (1);
	*err = curr_token(tokenlist_node);
    return (0);
}

t_ast_node	*program(t_tokenlist_node **tokenlist_node, t_token **err)
{
	t_ast_node	*root;

	if (*tokenlist_node == NULL)
		return (0);
	root = new_ast_node(0, AND_OR, NULL, 2);
	if (root == NULL)
		return (NULL);
	if (and_or(tokenlist_node, root, err))
		return (root);
	clear_ast(root);
	return (NULL);
}

int	and_or(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL, 2));
	add_ast_node_child(curr, new_ast_node(1, AND_OR_, NULL, 2));
	if (pipe_sequence(tokenlist_node, curr->child[0], err))
		return (and_or_(tokenlist_node, curr->child[1], err));
	return (0);
}

int	and_or_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{	
	if (*tokenlist_node == NULL)
		return (1);
	if (curr_tokentype(tokenlist_node) == AND_IF || \
	curr_tokentype(tokenlist_node) == OR_IF)
		curr->token = curr_token(tokenlist_node);
		add_ast_node_child(curr, new_ast_node(0, PIPE_SEQUENCE, NULL, 2));
		add_ast_node_child(curr, new_ast_node(1, AND_OR_, NULL, 3));
	if (accept(AND_IF, tokenlist_node))
	{
		if (pipe_sequence(tokenlist_node, curr->child[1], err))
			return (and_or_(tokenlist_node, curr->child[2], err));
	}
	else if (expect(OR_IF, tokenlist_node, err))
	{
		if (pipe_sequence(tokenlist_node, curr->child[1], err))
			return (and_or_(tokenlist_node, curr->child[2], err));
	}
	return (0);
}

int	pipe_sequence(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	if (*tokenlist_node == NULL)
		return (0);
	add_ast_node_child(curr, new_ast_node(0, COMMAND, NULL, 2));
	add_ast_node_child(curr, new_ast_node(1, PIPE_SEQUENCE_, NULL, 2));
	if (command(tokenlist_node, curr->child[0], err))
		return (pipe_sequence_(tokenlist_node, curr->child[1], err));
	return (0);
}

int	pipe_sequence_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	if (*tokenlist_node == NULL)
		return (1);
	if (curr_tokentype(tokenlist_node) == PIPE)
	{
		add_ast_node_child(curr, new_ast_node(0, COMMAND, NULL, 2));
		add_ast_node_child(curr, new_ast_node(1, PIPE_SEQUENCE_, NULL, 2));
	}
	if (accept(PIPE, tokenlist_node))
	{
		if (command(tokenlist_node, curr->child[1], err))
			return (pipe_sequence_(tokenlist_node, curr->child[2], err));
	}
	return (0);
}

int	command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	if (*tokenlist_node == NULL)
		return (0);
	if (curr_tokentype(tokenlist_node) == LPAREN)
	{
		add_ast_node_child(curr, new_ast_node(0, SUBSHELL, NULL, 1));
		add_ast_node_child(curr, new_ast_node(1, REDIRECT_LIST, NULL, 2));
		if (subshell(tokenlist_node, curr->child[0], err))
			return (redirect_list(tokenlist_node, curr->child[1], err));
	}
	else
	{
		add_ast_node_child(curr, new_ast_node(0, SIMPLE_COMMAND, NULL, 3));
		return (simple_command(tokenlist_node, curr->child[0], err));
	}
	return (0);
}

int	simple_command(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, CMD_PREFIX, NULL, 2));
	if (cmd_prefix(tokenlist_node, curr->child[0], err))
	{
		add_ast_node_child(curr, new_ast_node(1, CMD_WORD, NULL, 1));
		if (cmd_word(tokenlist_node, curr->child[1], err))
		{
			add_ast_node_child(curr, new_ast_node(2, CMD_SUFFIX, NULL, 2));
			return (cmd_suffix(tokenlist_node, curr->child[2], err));
		}
		free_ast_node(curr->child[1]);
		return (1);
	}
	else if (err != NULL)
		return (0);
	else
	{
		free_ast_node(curr->child[0]);
		add_ast_node_child(curr, new_ast_node(0, CMD_NAME, curr_token(tokenlist_node), 0));
		add_ast_node_child(curr, new_ast_node(1, CMD_SUFFIX, curr_token(tokenlist_node), 0));
		if (cmd_name(tokenlist_node, curr->child[0], err))
			if (cmd_suffix(tokenlist_node, curr->child[1], err))
				return (1);
	}
	return (0);
}

int	cmd_name(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	curr->token = curr_token(tokenlist_node);
	if (expect(WORD, tokenlist_node, err))
		return (1);
	else
		free_ast_node(curr);
	return (0);
}

int	cmd_word(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	curr->token = curr_token(tokenlist_node);
	return (expect(WORD, tokenlist_node, err));
}

int	cmd_prefix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1));
	add_ast_node_child(curr, new_ast_node(1, CMD_PREFIX, NULL, 2));
	if (io_redirect(tokenlist_node, curr->child[0], err))
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	else if (*err != NULL)
		return (0);
	else if (expect(ASSIGNMENT_WORD, tokenlist_node, err))
	{
		free_ast_node(curr->child[0]);
		add_ast_node_child(curr, new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 0));
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	}
	return (0);
}

int	cmd_prefix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1));
	add_ast_node_child(curr, new_ast_node(1, CMD_PREFIX, NULL, 2));
	if (io_redirect(tokenlist_node, curr->child[0], err))
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	else if (*err != NULL)
		return (0);
	else if (expect(ASSIGNMENT_WORD, tokenlist_node, err))
	{
		free_ast_node(curr->child[0]);
		add_ast_node_child(curr, new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 0));
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	}
	return (1);
}
