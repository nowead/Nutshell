/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:11:45 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/26 19:59:54 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_argv(t_ast_node *curr, char **argv)
{
	if (curr->child_num == 2)
	{
		if (add_argument_from_tokenlist(argv, curr->child[0]->tokenlist))
			return (-1);
		if (exec_cmd_suffix_argument(curr->child[1], argv))
			return (-1);
	}
	else if (curr->child_num == 3)
	{
		if (add_argument_from_tokenlist(argv, curr->child[1]->tokenlist))
			return (-1);
		if (exec_cmd_suffix_argument(curr->child[2], argv))
			return (-1);
	}
	return (0);
}

int	add_argument_from_tokenlist(char **argv, t_tokenlist *tokenlist)
{
	t_toknode	*curr;

	curr = tokenlist->head;
	while (curr)
	{
		if (add_argument(argv, curr->token->str))
			return (-1);
		curr = curr->next;
	}
	return (0);
}

int	add_argument(char **argv, char *arg)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	argv[i] = ft_strdup(arg);
	if (argv[i] == NULL)
		return (err_return(-1, "ft_strdup"));
	return (0);
}
