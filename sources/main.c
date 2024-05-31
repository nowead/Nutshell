/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/31 22:47:08 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    // Example usage
    // Assuming you have functions to create and populate the AST nodes

    // Example of creating and printing a simple AST node
    // t_tokenlist	*tokenlist;
	t_ast_node	*root;
    
    // Call the print function
	// tokenlist = tokenize("ls <");
	root = parse("ls << ||");
	print_ast(root, 0);

    return (0);
}
