/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:24:23 by damin             #+#    #+#             */
/*   Updated: 2024/06/13 15:44:23 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd[0])
		err_ctrl("Command error", 0, EXIT_FAILURE);
	if (ft_strchr(cmd[0], '/') != 0 && access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else
		path = check_path(cmd[0], envp);
	if (!path)
	{
		free_list(cmd);
		err_ctrl("No path adaptable", 0, 127);
	}
	if (execve(path, cmd, envp) == -1)
		err_ctrl("execve failed", 1, 127);
}

void	first_process(char **av, char **envp, int *fd)
{
	pid_t	pid;
	int		f_in;

	pid = fork();
	if (pid == -1)
		err_ctrl("fork fail ", 1, EXIT_FAILURE);
	if (pid == 0)
	{
		f_in = open_file(av[1], 0);
		if (dup2(f_in, STDIN_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if (close(f_in) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		exec(av[2], envp);
	}
}

void	child_process(char *av, char **envp, int *fd)
{
	pid_t	pid;

	if (dup2(fd[0], fd[2]) == -1)
		err_ctrl("dup2 error ", 1, EXIT_FAILURE);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		err_ctrl("close error ", 1, EXIT_FAILURE);
	if (pipe(fd) == -1)
		err_ctrl("pipe generate fail", 1, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		err_ctrl("fork fail ", 1, EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(fd[2], STDIN_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		exec(av, envp);
	}
	if (close(fd[2]) == -1)
		err_ctrl("close error ", 1, EXIT_FAILURE);
}

void	last_process(char **av, int ac, char **envp, int *fd)
{
	pid_t	pid;
	int		f_out;

	if (dup2(fd[0], fd[2]) == -1)
		err_ctrl("dup2 error ", 1, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		err_ctrl("fork fail ", 1, EXIT_FAILURE);
	if (pid == 0)
	{
		if (is_here_doc(av))
			f_out = open_file(av[ac - 1], 1);
		else
			f_out = open_file(av[ac - 1], 2);
		if (dup2(fd[2], STDIN_FILENO) == -1)
			err_ctrl("dup2 error ", 1, EXIT_FAILURE);
		if (dup2(f_out, STDOUT_FILENO) == -1)
			err_ctrl("dup2 error", 1, EXIT_FAILURE);
		if (close(f_out) == -1 || close(fd[0]) == -1 \
		|| close(fd[1]) == -1 || close(fd[2]) == -1)
			err_ctrl("close error ", 1, EXIT_FAILURE);
		exec(av[ac - 2], envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		fd[3];
	int		i;

	if (ac < 5)
		err_ctrl("invaild input.", 0, EXIT_FAILURE);
	i = 2;
	fd[2] = valid_fd();

	if (pipe(fd) == -1)
		err_ctrl("pipe generate fail", 1, EXIT_FAILURE);


	if (!is_here_doc(av))
		first_process(av, envp, fd);
	else
		here_doc_process(av, fd);

	while (++i < ac - 2)
		child_process(av[i], envp, fd);

	last_process(av, ac, envp, fd);


	if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(fd[2]) == -1)
		err_ctrl("close error ", 1, EXIT_FAILURE);
	while (i-- > 1)
		wait(0);
	return (0);
}
