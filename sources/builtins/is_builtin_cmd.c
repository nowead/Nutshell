/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 01:28:33 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/12 01:42:13 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_cmd(t_ast_node *curr)
{
	char	*cmd_name;

	if (curr->sym == SUBSHELL)
		return (0);
	if (curr->child_num == 2)
		cmd_name = curr->child[0]->token->str;
	else if (curr->child_num == 3)
		cmd_name = curr->child[1]->token->str;
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (1);
	return (0);
}
