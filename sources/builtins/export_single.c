/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:22:10 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/17 17:34:57 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_print_envp(char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x ");
		printf("%.*s", (int)get_key_len(envp[i]), envp[i]);
		if (ft_strchr(envp[i], '='))
		{
			printf("=\"");
			printf("%s", ft_strchr(envp[i], '=') + 1);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	return (0);
}
