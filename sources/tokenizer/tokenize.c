/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:53:49 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/08 21:47:55 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokenlist	*tokenize(const char *input, int *incomplete_cmd)
{
	t_tokenlist	*tokenlist;

	if (input == NULL)
		return (NULL);
	tokenlist = new_tokenlist();
	if (tokenlist == NULL)
	{
		perror("tokenlist allocation fail");
		return (NULL);
	}
	if (process_tokens(input, tokenlist, incomplete_cmd) == -1)
	{
		clear_tokenlist(tokenlist);
		return (NULL);
	}
	return (tokenlist);
}

int	process_tokens(const char *input, t_tokenlist *tokenlist, \
int *incomplete_cmd)
{
	t_tokentype				tokentype;
	t_quotetype				quotetype;
	size_t					tok_start;
	size_t					i;
	t_token_handler_args	args;

	quotetype = NO_QUOTE;
	tokentype = TOK_UNKNOWN;
	args = (t_token_handler_args){input, &tok_start, \
			&tokentype, &quotetype, tokenlist};
	i = 0;
	while (input[i])
	{
		if (handle_token_creation(&args, &i) == -1)
			return (-1);
	}
	if (quotetype != NO_QUOTE)
	{
		*incomplete_cmd = 1;
		return (-1);
	}
	else if (add_final_token(&args, i) == -1)
		return (-1);
	return (0);
}

int	add_final_token(t_token_handler_args *args, size_t i)
{
	if (*(args->tokentype) == TOK_WORD)
	{
		if (tokenlist_add(args->tokenlist, \
		new_word_token(ft_substr(args->input, *(args->tok_start), \
		i - *(args->tok_start)))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	else if (*(args->tokentype) >= TOK_LPAREN)
	{
		if (tokenlist_add(args->tokenlist, \
		new_operator_token(*(args->tokentype))) == -1)
		{
			perror("token allocation fail");
			return (-1);
		}
	}
	if (tokenlist_add(args->tokenlist, new_operator_token(TOK_NEWLINE)) == -1)
	{
		perror("token allocation fail");
		return (-1);
	}
	return (0);
}
