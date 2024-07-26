/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:13:24 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/26 21:18:20 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_parameters_in_simple_command(t_ast_node *curr, \
t_shell_ctx *shell_ctx)
{
	if (expand_parameters_in_cmd_name(curr, shell_ctx))
		return (-1);
	if (curr->child_num == 2)
		curr = curr->child[1];
	else
		curr = curr->child[2];
	while (curr->child)
	{
		if (curr->child[0]->sym == TERMINAL)
		{
			curr->child[0]->tokenlist = \
			expand_parameters_in_a_token(curr->child[0]->token, shell_ctx);
			if (curr->child[0]->tokenlist == NULL)
				return (-1);
		}
		curr = curr->child[1];
	}
	return (0);
}

int	expand_parameters_in_cmd_name(t_ast_node *curr, t_shell_ctx *shell_ctx)
{
	if (curr->child_num == 2)
	{
		curr->child[0]->tokenlist = \
		expand_parameters_in_a_token(curr->child[0]->token, shell_ctx);
		if (curr->child[0]->tokenlist == NULL)
			return (-1);
	}
	else
	{
		curr->child[1]->tokenlist = \
		expand_parameters_in_a_token(curr->child[1]->token, shell_ctx);
		if (curr->child[1]->tokenlist == NULL)
			return (-1);
	}
	return (0);
}
