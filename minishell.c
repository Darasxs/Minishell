/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daras <daras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/17 10:17:06 by daras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	preparing_execution(minishell_t *line)
{
	if (check_builtin_commands(line))
		return ;
	path_preparation(line);
	line->path = find_path(line->split_commands[0], line);
	if (!line->path)
		ft_error("Command not found\n", NULL);
}

void	execute_command(minishell_t *line, int input_fd, int output_fd)
{
	preparing_execution(line);
	if(line->path)
	{
		if(input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if(output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		if (execve(line->path, line->split_commands, NULL) == -1)
		{
			ft_error("Execution failed\n", NULL);
			free(line->path);
		}
	}
	free(line->path);
}

void	minishell(minishell_t *line)
{
	pid_t	pid;
	int		fd[2];
	char	**commands;
	size_t	i;

	i = 0;
	printing_prompt(line);
	if (line->input)
	{
		add_history(line->input);
		commands = ft_split(line->input, '|');
		while(commands[i])
		{
			line->split_commands = ft_split(commands[i], ' ');
			if(commands[i + 1])
			{
				if(pipe(fd) == -1)
				{
					free_split(commands);
					ft_error("Error occured while creating pipe\n", NULL);
				}
			}
			else
				fd[1] = STDOUT_FILENO;
			pid = fork();
			if (pid == 0)
			{
				execute_command(line, STDIN_FILENO, fd[1]);
				exit(0);	
			}
			else if (pid < 0)
			{
				free_split(line->split_commands);
				ft_error("Error occured while forking\n", NULL);
			}
			else if (pid > 0)
			{
				wait(NULL);
				close(fd[1]);
				if(fd[0] != STDIN_FILENO)
					close(fd[0]);
				fd[0] = STDIN_FILENO;
			}
			free_split(line->split_commands);
			i++;
		}
		free_split(commands);
	}
	cleanup(line);
}
