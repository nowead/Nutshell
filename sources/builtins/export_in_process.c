/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_in_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:39:06 by damin             #+#    #+#             */
/*   Updated: 2024/07/11 16:47:53 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export_in_process(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_name(argv[i], ft_strlen(argv[i])))
		{
			ft_dprintf(STDERR_FILENO, \
			"`%s': not a valid identifier\n", argv[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	exit(EXIT_SUCCESS);
}
