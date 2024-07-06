/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/07/06 21:00:21 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_shell_context *shell_ctx)
{
	printf("\033[u\033[1B\033[1A");
	printf("\nexit\n");
	restore_echoctl(&(shell_ctx->old_term));
	exit(EXIT_SUCCESS);
}
