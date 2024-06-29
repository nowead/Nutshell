/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/06/29 20:22:44 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "minishell.h"

void    exec_echo(char **argv)
{
	int i;
	int	n_flag_on;

	i = 1;
	n_flag_on = 0;
	while (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
	{
		n_flag_on = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s",argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (!n_flag_on)
		printf("\n");
	exit(EXIT_SUCCESS);
}

int	exec_cd(char *path)
{
	char			*cwd;
	DIR				*dir;
	struct dirent	*entry;

	if (chdir(path) == -1)
        err_return("chdir");
    dir = opendir(".");
    if (dir == NULL)
		err_return("opendir");
    // 디렉토리 내용 출력
    // printf("디렉토리 내용:\n");
    // while ((entry = readdir(dir)) != NULL)
	// {
    //     // "." 과 ".." 는 출력하지 않음
    //     if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
    //         printf("  %s\n", entry->d_name);
    //     }
    // }
    // 디렉토리 스트림 닫기
    if (closedir(dir) == -1)
		err_return("closedir");
	return (0);
}

int	exec_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		err_return("getcwd");
    printf("%s\n", cwd);
	free(cwd);
	return (0);
}

void	exec_env(t_shell_context *shell_ctx)
{
	size_t	i;
	char	**envp;

	envp = *(shell_ctx->envp);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

void	exec_exit(t_shell_context *shell_ctx)
{
	printf("\033[u\033[1B\033[1A");
	printf("\nexit\n");
	restore_echoctl(&(shell_ctx->old_term));
	exit(EXIT_SUCCESS);
}
