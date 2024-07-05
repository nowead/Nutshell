/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:24:01 by damin             #+#    #+#             */
/*   Updated: 2024/07/05 19:40:30 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define USE_READLINE
#include "minishell.h" 

int main()
{
    char	*line;

	line = "none";
	while (line != 0)
	{
		printf("> \033[s\b\b");
		line = readline("> ");
		if (!line)
		{
            sleep(2);
			printf("\033[u\033[1B\033[1A");
            printf("\b\b");
			break ;
		}
		if (ft_strlen(line) == 4 && ft_strncmp(line, "EOF", ft_strlen(line)) == 0)
			break ;
		free(line);
	}
	free(line);
}