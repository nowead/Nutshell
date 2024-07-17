/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:02:22 by damin             #+#    #+#             */
/*   Updated: 2024/07/17 14:00:12 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint_flag = 0;

// int custom_rl_getc() 
// {
//     unsigned char c;
	
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

int	run_shell(char *envp[])
{
	t_shell_ctx		shell_ctx;

	// rl_getc_function = custom_rl_getc;
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
	char	*old_line;
	t_ast	*ast;
	int		incomplete_cmd;

	old_line = NULL;
	incomplete_cmd = 0;
	while (1)
	{
		line = display_prompt_and_read_input(incomplete_cmd);
		if (handle_input(shell_ctx, &incomplete_cmd, old_line, &line))
			continue ;
		ast = parse(line, &incomplete_cmd, shell_ctx);
		if (update_signal_and_old_line(&incomplete_cmd, &old_line, line))
			continue ;
		execute_parsed_command(ast, shell_ctx, line);
		free(line);
	}
}

int	update_signal_and_old_line(int *incomplete_cmd, char **old_line, char *line)
{
	if (*incomplete_cmd)
	{
		set_signal_handler(SIGINT_INCOMPLETE_CMD_HANDLER);
		*old_line = line;
		return (1);
	}
	else
	{
		set_signal_handler(SIGINT_HANDLER);
		return (0);
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
