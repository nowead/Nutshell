/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/06/27 17:01:37 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_echo(char **argv, char **envp)
{
	int i;
	int	n_flag_on;

	i = 1;
	n_flag_on = 0;
	while (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
	{
		n_flag_on = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s",argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (!n_flag_on)
		printf("\n");
}

void	exec_exit(char **argv, char **envp)
{
	
}