/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:11:45 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/25 22:12:07 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_argv(t_ast_node *curr, char **argv)
{
	if (curr->child_num == 2)
	{
		add_argument_from_tokenlist(argv, curr->child[0]->tokenlist);
		exec_cmd_suffix_argument(curr->child[1], argv);
	}
	else if (curr->child_num == 3)
	{
		add_argument_from_tokenlist(argv, curr->child[1]->tokenlist);
		exec_cmd_suffix_argument(curr->child[2], argv);
	}
}

void	add_argument_from_tokenlist(char **argv, t_tokenlist *tokenlist)
{
	t_toknode	*curr;

	curr = tokenlist->head;
	while (curr)
	{
		add_argument(argv, curr->token->str);
		curr = curr->next;
	}
}

void	add_argument(char **argv, char *arg)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	argv[i] = ft_strdup(arg);
	if (argv[i] == NULL)
		err_exit("add_argument", 1, EXIT_FAILURE);
}
