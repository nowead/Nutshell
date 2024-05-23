/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/05/23 22:14:18 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = tokenize("ssd=f )((|(r=1&&<dsf>||sdf=2314| )esf ");
	if (print_tokenlist(tokenlist) == -1)
		tokenize_err_exit(tokenlist, "fail to print tokenlist");
	ft_printf("size:%d\n", tokenlist->size);
	tokenlist_clear(tokenlist);
}
