/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:57:38 by damin             #+#    #+#             */
/*   Updated: 2024/06/21 17:35:43 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_READLINE
#include "minishell.h"

void	ctrl_cmd(t_ast *ast)
{
	if (ast != NULL)
	{
		print_ast(ast->root, 0);
		print_tokenlist(ast->tokenlist);
		ft_printf("\n\n");
	}
	if (ast != NULL && ast->root)
	{
		e_and_or(ast->root);
	}
}
