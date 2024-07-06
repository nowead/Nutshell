/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:45:48 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/06 20:48:44 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenizer.h"
# include "parser.h"
# include "executor.h"
# include "interface.h"
# include "builtins.h"
# include "utilities.h"

extern int  sigint_flag;

#endif
