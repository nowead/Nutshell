/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/07/18 13:42:17 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint_flag = 0;

// int custom_rl_getc() 
// {
//     unsigned char c;
//	
//     if (read(STDIN_FILENO, &c, 1) == 1)
// 	{
//         if (c == 12)
// 		{
//             printf("\033[H\033[J"); // 화면 지우기
//             rl_on_new_line();
//             rl_redisplay();
// 			printf("\033[s");
//             return 0; // 입력 스트림에 '\0' 반환
//         }
//         return c;
//     }
//     return EOF;
// }
//
// rl_getc_function = custom_rl_getc;

int	run_shell(char *envp[])
{
	t_shell_ctx		shell_ctx;

	set_echoctl(&(shell_ctx.old_term), ECHOCTL_OFF);
	init_signal_handler();
	init_shell_ctx(&shell_ctx, envp);
	backup_stdfd(&shell_ctx);
	shell_main_loop(&shell_ctx);
	return (0);
}

void	shell_main_loop(t_shell_ctx *shell_ctx)
{
	char	*line;
	t_ast	*ast;

	while (1)
	{
		line = readline("Nutshell $ ");
		if (handle_input(shell_ctx, &line))
			continue ;
		ast = parse(line, shell_ctx);
		execute_parsed_command(ast, shell_ctx, line);
		free(line);
	}
}

void	execute_parsed_command(t_ast *ast, t_shell_ctx *shell_ctx, char *line)
{
	if (ast == NULL)
		return ;
	exec_ast(ast, shell_ctx);
	restore_stdfd(shell_ctx);
	clear_ast(ast);
	add_history(line);
}
