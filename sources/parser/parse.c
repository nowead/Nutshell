/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/23 21:39:37 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		dprintf(2, "syntax error near unexpected token: %s\n", \
		tokentype_to_str(curr_token(tokenlist_node)));
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
	if (*tokenlist_node == NULL)
		return (NULL);
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
	if (and_or(tokenlist_node, root, err) && *tokenlist_node == NULL)
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
	else if (accept(OR_IF, tokenlist_node))
	{
		if (pipe_sequence(tokenlist_node, curr->child[1], err))
			return (and_or_(tokenlist_node, curr->child[2], err));
	}
	if (*err != NULL)
		return (0);
	return (1);
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
	if (*err != NULL)
		return (0);
	return (1);
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

int	subshell(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
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
	else if (*err == NULL)
	{
		free_ast_node(curr->child[0]);
		add_ast_node_child(curr, new_ast_node(0, CMD_NAME, curr_token(tokenlist_node), 0));
		add_ast_node_child(curr, new_ast_node(1, CMD_SUFFIX, curr_token(tokenlist_node), 0));
		if (cmd_name(tokenlist_node, curr->child[0], err))
			return (cmd_suffix(tokenlist_node, curr->child[1], err));
	}
	return (0);
}

int	cmd_name(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	curr->token = curr_token(tokenlist_node);
	return (expect(WORD, tokenlist_node, err));
}

int	cmd_word(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	curr->token = curr_token(tokenlist_node);
	return (accept(WORD, tokenlist_node));
}

int	cmd_prefix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1));
	add_ast_node_child(curr, new_ast_node(1, CMD_PREFIX, NULL, 2));
	if (io_redirect(tokenlist_node, curr->child[0], err))
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	else if (*err == NULL && accept(ASSIGNMENT_WORD, tokenlist_node))
	{
		free_ast_node(curr->child[0]);
		add_ast_node_child(curr, new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 0));
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	}
	free_ast_node(curr->child[0]);
	free_ast_node(curr->child[1]);
	return (0);
}

int	cmd_prefix_(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1));
	add_ast_node_child(curr, new_ast_node(1, CMD_PREFIX, NULL, 2));
	if (io_redirect(tokenlist_node, curr->child[0], err))
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	else if (*err == NULL && accept(ASSIGNMENT_WORD, tokenlist_node))
	{
		free_ast_node(curr->child[0]);
		add_ast_node_child(curr, new_ast_node(0, TERMINAL, curr_token(tokenlist_node), 0));
		return (cmd_prefix_(tokenlist_node, curr->child[1], err));
	}
	if (*err != NULL)
		return (0);
	free_ast_node(curr->child[0]);
	free_ast_node(curr->child[1]);
	return (1);
}

int	cmd_suffix(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(1, CMD_SUFFIX, NULL, 2));
	if (accept(WORD, tokenlist_node))
	{
		add_ast_node_child(curr, new_ast_node(0, WORD, curr_token(tokenlist_node), 0));
		return (cmd_suffix(tokenlist_node, curr->child[1], err));
	}
	else
	{
		add_ast_node_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1));
		if (io_redirect(tokenlist_node, curr->child[0], err))
			return (cmd_suffix(tokenlist_node, curr->child[1], err));
	}
	if (err != NULL)
		return (0);
	free_ast_node(curr->child[0]);
	free_ast_node(curr->child[1]);
	return (1);
}

int	redirect_list(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, IO_REDIRECT, NULL, 1));
	if (io_redirect(tokenlist_node, curr->child[0], err))
	{
		add_ast_node_child(curr, new_ast_node(0, REDIRECT_LIST, NULL, 2));
		return (redirect_list(tokenlist_node, curr->child[1], err));
	}
	if (err != NULL)
		return (0);
	free_ast_node(curr->child[0]);
	return (1);
}

int	io_redirect(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, IO_FILE, NULL, 1));
	if (io_file(tokenlist_node, curr->child[0], err))
		return (1);
	free_ast_node(curr->child[0]);
	add_ast_node_child(curr, new_ast_node(0, IO_HERE, NULL, 1));
	return (io_here(tokenlist_node, curr->child[0], err));
}

int	io_file(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, FILENAME, NULL, 0));
	if (accept(LESS, tokenlist_node) || accept(GREAT, tokenlist_node) || \
	accept(DGREAT, tokenlist_node))
	{
		curr->token = curr_token(tokenlist_node);
		return (filename(tokenlist_node, curr->child[0], err));
	}
	free_ast_node(curr->child[0]);
	return (0);
}

int	filename(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	curr->token = curr_token(tokenlist_node);
	return (expect(WORD, tokenlist_node, err));
}

int	io_here(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	add_ast_node_child(curr, new_ast_node(0, HERE_END, NULL, 0));
	if (accept(DLESS, tokenlist_node))
	{
		curr->token = curr_token(tokenlist_node);
		return (here_end(tokenlist_node, curr->child[0], err));
	}
	free_ast_node(curr->child[0]);
	return (0);
}

int	here_end(t_tokenlist_node **tokenlist_node, t_ast_node *curr, t_token **err)
{
	curr->token = curr_token(tokenlist_node);
	return (expect(WORD, tokenlist_node, err));
}
