/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:27:34 by damin             #+#    #+#             */
/*   Updated: 2024/06/07 17:00:24 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	e_and_or()
{
	e_pipe_sequence();
	e_and_or_();
}

int e_and_or_()
{
	
}

int e_pipe_sequence()
{
	e_cmd();
	e_pipe_sequence_();
}

int e_pipe_sequence_()
{
	e_cmd();
	e_pipe_sequence_();
}

int simple_cmd()
{
	
}
	// simple_command   : cmd_prefix cmd_word cmd_suffix
	//              | cmd_prefix
	//              | cmd_name cmd_suffix
	//              ;
