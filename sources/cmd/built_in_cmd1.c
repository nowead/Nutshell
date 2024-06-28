/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:48 by damin             #+#    #+#             */
/*   Updated: 2024/06/28 22:06:17 by damin            ###   ########.fr       */
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

void	exec_exit(t_shell_context *shell_ctx)
{
	printf("\033[u\033[1B\033[1A");
	printf("\nexit\n");
	restore_echoctl(&(shell_ctx->old_term));
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

int	exec_export(char **argv, char ***envp)
{
	
}

int	exec_export_single_key(char *arg, char ***envp)
{
	// size_t	envp_len;
	// char	**new_envp;

	// search_env()
	// envp_len = ft_strslen(*envp);
	// new_envp = (char **)ft_calloc(envp_len + 2, sizeof(char *));
	// if (new_envp == NULL)
	// 	return (err_return("malloc"));
	// ft_memcpy(new_envp, *envp, envp_len + 2);
	// ft_memcpy(new_envp + envp_len, curr->token->str, envp_len + 2);
	// free(*envp);
	// *envp = new_envp;
	return (0);
}

char	**search_env(const char *key, char *envp[])
{
	size_t	i;
	size_t	len;

	if (key == NULL)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_strslen(char **strs)
{
	size_t	len;

	len = 0;
	while (strs[len])
		len++;
	return (len);
}