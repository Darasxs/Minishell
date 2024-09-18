/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/18 14:47:52 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(minishell_t *line, int input_fd, int output_fd)
{
	preparing_execution(line);
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

void	minishell(minishell_t *line)
{
	pid_t pid;
	int fd[2];
	int input_fd;
	char **commands;
	size_t i = 0;

	input_fd = STDIN_FILENO;
	printing_prompt(line);
	if (line->input)
	{
		add_history(line->input);
		commands = ft_split(line->input, '|');
		while (commands[i])
		{
			line->split_commands = ft_split(commands[i], ' ');
			if (commands[i + 1] && pipe(fd) == -1)
				ft_error("Error occurred while creating pipe\n", NULL, line);
			if (check_builtin(line))
				free_split(line->split_commands);
			else
			{
				pid = fork();
				if (pid < 0)
					ft_error("Error occurred while forking\n", NULL, line);
				else if (pid == 0)
				{
					if (i > 0)
						dup2(input_fd, STDIN_FILENO);
					if (commands[i + 1])
						dup2(fd[1], STDOUT_FILENO);
					else
						fd[1] = STDOUT_FILENO;
					execute_command(line, STDIN_FILENO, fd[1]);
					exit(0);
				}
				else
				{
					wait(NULL);
					close(fd[1]);
					if (input_fd != STDIN_FILENO)
						close(input_fd);
					input_fd = fd[0];
				}
			}
			i++;
		}
		free_split(commands);
	}
	cleanup(line);
}
