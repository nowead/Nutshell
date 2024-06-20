/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/06/20 19:50:48 by seonseo          ###   ########.fr       */
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
	// clear_tokenlist(tokenlist);
	// return (0);
}
