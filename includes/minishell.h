/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:45:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/18 13:22:24 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <string.h>
# include "libft.h"
# include "tokenizer.h"
# include "parser.h"
# include "executor.h"
# include "interface.h"
# include "builtins.h"
# include "utilities.h"

extern int	g_sigint_flag;

#endif
