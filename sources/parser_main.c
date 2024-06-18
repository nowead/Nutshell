/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/18 20:27:30 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	leak_check(void)
// {
// 	system("leaks parser");
// }

int main()
{
	// atexit(leak_check);
	prompt();
    return (0);
	// t_tokenlist	*tokenlist;

	// atexit(leak_check);
	// tokenlist = tokenize("a b c");
	// expand_parameter(tokenlist);
	// print_tokenlist(tokenlist);
	// tokenlist_clear(tokenlist);
	// return (0);
}
