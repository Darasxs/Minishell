/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/19 18:49:38 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(minishell_t *line, int input_fd, int output_fd)
{
	preparing_execution(line);
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
	if(execve(line->path, line->split_commands, NULL) == -1)
		ft_error("Execution failed.\n", NULL, line);
	free(line->path);
}

void	minishell(minishell_t *line)
{
	pid_t	pid;
	size_t	i;
	size_t	j;
	char	**commands;
	int		fd[2];
	int		input_fd;
	int		status;

	i = 0;
	input_fd = STDIN_FILENO;
	printing_prompt(line);
	if(line->input)
	{
		add_history(line->input);
		commands = ft_split(line->input, '|');
		
		while(commands[i])
		{
			line->split_commands = ft_split(commands[i], ' ');
			j = 0;
			while(commands[j])
				j++;
			if(commands[i + 1] && pipe(fd) == -1)
				ft_error("Error occured while craeting a pipe.\n", NULL, line);
			if(line->split_commands[0] && ft_strncmp(line->split_commands[0], "cd", 3) == 0)
			{
				if(j == 1 || i == j - 1)
					cd_builtin(line);
				if(commands[i + 1])
				{
					close(fd[1]);
					input_fd = fd[0];
				}
			}
			else
			{
				pid = fork();
				if(pid < 0)
					ft_error("Error occured while forking.\n", NULL, line);
				else if(pid == 0)
				{
					if(i > 0)
					{
						dup2(input_fd, STDIN_FILENO);
						close(input_fd);
					}
					if (commands[i + 1])
					{
						dup2(fd[1], STDOUT_FILENO);
						close(fd[1]);
					}
					if(check_builtin(line))
						exit(0);
					else
						execute_command(line, STDIN_FILENO, STDOUT_FILENO);
					exit(0);
				}
				else
				{
					waitpid(pid, &status, 0);
					if(commands[i + 1])
					{
						close(fd[1]);
						if(input_fd != STDIN_FILENO)
							close(input_fd);
						input_fd = fd[0];
					}
					if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
						break;
				}
			}
			free_split(line->split_commands);
			i++;
		}
		free_split(commands);
	}
	cleanup(line);
}





