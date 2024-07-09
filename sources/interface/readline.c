/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt_and_read_input.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 03:23:59 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/10 03:24:08 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_prompt_and_read_input(int incomplete_cmd)
{
	if (!incomplete_cmd)
		printf("Nutshell $ \033[s\b\b\b\b\b\b\b\b\b\b\b");
	else
		printf("> \033[s\b\b");
	return (readline(get_prompt(incomplete_cmd)));
}

const char	*get_prompt(int incomplete_cmd)
{
	if (incomplete_cmd)
		return ("> ");
	else
		return ("Nutshell $ ");
}
