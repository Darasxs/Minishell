/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/20 18:51:15 by paprzyby         ###   ########.fr       */
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
	if (line->input)
	{
		add_history(line->input);
		commands = ft_split(line->input, '|');
		while (commands[i])
		{
			line->split_commands = ft_split(commands[i], ' ');
			j = 0;
			while (commands[j])
				j++;
			if (commands[i + 1] && pipe(fd) == -1)
				ft_error("Error occured while creating a pipe.\n", NULL, line);
			if (check_builtin(line))
			{
				if (check_cd(line))
				{
					if (j == 1 || i == j - 1)
						cd_builtin(line);
				}
				execute_builtin(line);
				if (commands[i + 1])
				{
					close(fd[1]);
					input_fd = fd[0];
				}
			}
			else
			{
				pid = fork();
				if (pid < 0)
					ft_error("Error occured while forking.\n", NULL, line);
				else if (pid == 0)
				{
					if (i > 0)
					{
						dup2(input_fd, STDIN_FILENO);
						close(input_fd);
					}
					if (commands[i + 1])
					{
						dup2(fd[1], STDOUT_FILENO);
						close(fd[1]);
					}
					close(fd[0]);
					execute_command(line);
					exit(0);
				}
				else
				{
					if (commands[i + 1])
					{
						close(fd[1]);
						if (input_fd != STDIN_FILENO)
							close(input_fd);
						input_fd = fd[0];
					}
					else
						close(fd[0]);
				}
			}
			free_split(line->split_commands);
			i++;
		}
		while (waitpid(-1, &status, 0) > 0)
			if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
				exit(1);
		free_split(commands);
	}
	cleanup(line);
}
