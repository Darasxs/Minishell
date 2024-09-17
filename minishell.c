/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/17 17:56:20 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(minishell_t *line, int input_fd, int output_fd)
{
	if (line->path)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		if (execve(line->path, line->split_commands, NULL) == -1)
			ft_error("Execution failed\n", NULL, line);
		free(line->path);
	}
}

void	child_process(minishell_t *line, int i, int input_fd, int *fd)
{
	if (i > 0)
		dup2(input_fd, STDIN_FILENO);
	if (line->split_pipe[i + 1])
		dup2(fd[1], STDOUT_FILENO);
	else
		fd[1] = STDOUT_FILENO;
	execute_command(line, STDIN_FILENO, fd[1]);
	exit(0);
}

void	process(minishell_t *line, size_t i, int *fd)
{
	pid_t	pid;
	int 	input_fd;

	input_fd = STDIN_FILENO;
	if (!preparing_execution(line))
	{
		pid = fork();
		if (pid < 0)
			ft_error("Error occurred while forking\n", NULL, line);
		else if (pid == 0)
			child_process(line, i, input_fd, fd);
		else
		{
			wait(NULL);
			close(fd[1]);
			if (input_fd != STDIN_FILENO)
				close(input_fd);
			input_fd = fd[0];
		}
	}
}

void	minishell(minishell_t *line)
{
	int fd[2];
	size_t i;

	i = 0;
	printing_prompt(line);
	if (line->input)
	{
		add_history(line->input);
		line->split_pipe = ft_split(line->input, '|');
		while (line->split_pipe[i])
		{
			line->split_commands = ft_split(line->split_pipe[i], ' ');
			if (line->split_pipe[i + 1] && pipe(fd) == -1)
				ft_error("Error occurred while creating pipe\n", NULL, line);
			process(line, i, fd);
			free_split(line->split_commands);
			i++;
		}
		free_split(line->split_pipe);
	}
	cleanup(line);
}
