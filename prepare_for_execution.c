/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:43:50 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/24 17:27:47 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(minishell_t *line)
{
	preparing_execution(line);
	if (execve(line->path, line->split_commands, NULL) == -1)
		ft_error("Execution failed.\n", NULL, line);
	free(line->path);
}

void	handle_builtins(minishell_t *line, size_t i, char **commands,
		int *input_fd, int *fd)
{
	size_t	j;

	j = 0;
	while(commands[j])
		j++;
	if (check_cd(line))
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

void	handle_child_process(minishell_t *line, size_t i, int *input_fd,
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
	if (check_env(line))
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

void	execute_pipe_commands(minishell_t *line, char **commands, size_t i,
		int *input_fd)
{
	int		fd[2];
	pid_t	pid;

	line->split_commands = ft_split(commands[i], ' ');
	parsing(line);
	if (commands[i + 1] && pipe(fd) == -1)
		ft_error("Error occurred while creating a pipe.\n", NULL, line);
	if (check_builtin(line))
		handle_builtins(line, i, commands, input_fd, fd);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error("Error occurred while forking.\n", NULL, line);
		else if (pid == 0)
			handle_child_process(line, i, input_fd, fd, commands);
		else
		{
			handle_parent_process(i, input_fd, fd, commands);
			free_split(line->split_commands);
		}
	}
}
