/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_affixes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:29:43 by seonseo           #+#    #+#             */
/*   Updated: 2024/08/04 02:55:57 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_suffix_without_redirect(t_ast_node *curr, char **argv)
{
	while (curr->child)
	{
		if (curr->child[0]->token && curr->child[0]->token->type == TOK_WORD)
			if (builtin_add_argument(argv, curr->child[0]->token->str))
				return (-1);
		curr = curr->child[1];
	}
	return (0);
}

int	builtin_add_argument(char **argv, char *arg)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	argv[i] = ft_strdup(arg);
	if (argv[i] == NULL)
		return (err_return(1, "ft_strdup"));
	return (0);
}
