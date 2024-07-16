/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:13:36 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/16 14:27:31 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	leak_check(void)
// {
// 	system("leaks minishell");
// }

// void	signal_handler(int err)
// {
// 	write(1, "sigint is recieved\n", 20);
// 	g_sigint_flag = 1;
// }

// int main(int argc, char *argv[], char *envp[])
// {
// 	// atexit(leak_check);
// 	(void)argc;
// 	(void)argv;
// 	// run_shell(envp);
// 	// t_ast	*ast;
// 	// int		incomplete_cmd;

// 	// atexit(leak_check);
// 	// ast = parse("$a", &incomplete_cmd, envp);
// 	// if (ast != NULL && incomplete_cmd == 0)
// 	// {
// 	// 	print_ast(ast->root, 0);
// 	// 	clear_ast(ast);
// 	// }
// 	// else
// 	// 	printf("error!\n");
// 	char	*line;

// 	signal(SIGINT, signal_handler);
// 	printf("> ");
// 	line = gnl(0);
// 	printf("%s\n", line);
// 	return (0);
// }
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
    // Exit if needed, or just return to interrupt the read() call
    exit(0);
}

int main() {
    char    *line;
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = 0; // Clear all flags initially

    // Unset SA_RESTART to ensure system calls are interrupted
    action.sa_flags &= ~SA_RESTART;

    // Set the signal handler for SIGINT
    if (sigaction(SIGINT, &action, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

	printf("> ");
	line = gnl(0);
	printf("%s\n", line);
	return (0);

    return 0;
}