/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daras <daras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:58 by daras            ###   ########.fr       */
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

void	execute_command(minishell_t *line)
{
	preparing_execution(line);
	if(line->path)
	{
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
	// int		fd[2];
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
			pid = fork();
			if (pid == 0)
				execute_command(line);
			else if (pid < 0)
			{
				free_split(line->split_commands);
				ft_error("Error occured while forking\n", NULL);
			}
			else if (pid > 0)
			{
				wait(NULL);
				// close(fd[1]);
				// fd = fd[0];
			}
			free_split(line->split_commands);
			i++;
		}
		free_split(commands);
	}
	cleanup(line);
}
