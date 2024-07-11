/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:31:10 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/11 12:33:06 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(char **argv)
{
	int	i;
	int	n_flag_on;

	i = 1;
	n_flag_on = 0;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		n_flag_on = 1;
		i++;
	}
	while (argv[i] || (argv[i] && argv[i][0] == '\0'))
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i] || (argv[i] && argv[i][0] == '\0'))
			printf(" ");
	}
	if (!n_flag_on)
		printf("\n");
	exit(EXIT_SUCCESS);
}
