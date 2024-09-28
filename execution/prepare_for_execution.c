/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:43:50 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/28 05:24:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_builtins(t_minishell *line, size_t i, char **commands,
		int *input_fd, int *fd)
{
	size_t	j;

	j = 0;
	while(commands[j])
		j++;
	if (ft_strncmp(line->split_commands[0], "cd", 3) == 0)
	{
		if (j == 1 || i == j - 1)
			cd_builtin(line);
	}
	execute_builtin(line);
	if (commands[i + 1])
	{
		close(fd[1]);
		*input_fd = fd[0];
	}
}

void	handle_child_process(t_minishell *line, size_t i, int *input_fd,
		int *fd, char **commands)
{
	if (i > 0)
	{
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
	}
	if (commands[i + 1])
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	close(fd[0]);
	if (line->split_commands[0] && ft_strncmp(line->split_commands[0], "env",
			3) == 0)
		env_builtin(line);
	else
		execute_command(line);
	exit(0);
}

void	handle_parent_process(size_t i, int *input_fd, int *fd, char **commands)
{
	if (commands[i + 1])
	{
		close(fd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = fd[0];
	}
	else
	{
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		close(fd[0]);
	}
}

void	execute_pipe_commands(t_minishell *line, char **commands, size_t i,
		int *input_fd)
{
	int		fd[2];
	pid_t	pid;

	line->split_commands = ft_split(commands[i], ' ');
	parsing(line, commands);
	if (commands[i + 1] && pipe(fd) == -1)
		ft_error("Error occurred while creating a pipe\n", NULL, line);
	if (check_builtin(line))
		handle_builtins(line, i, commands, input_fd, fd);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error("Error occurred while forking\n", NULL, line);
		else if (pid == 0)
			handle_child_process(line, i, input_fd, fd, commands);
		else
		{
			handle_parent_process(i, input_fd, fd, commands);
			free_split(line->split_commands);
		}
	}
}
