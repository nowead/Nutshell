/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:59:54 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/18 17:22:06 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_parsetree_node *parse(const char* input)
{
	t_tokenlist			*tokenlist;
	t_parsetree_node	*root;

	tokenlist = tokenize(input);
	root = program(tokenlist);
	return (root);
}


