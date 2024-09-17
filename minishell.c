/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/14 11:36:20 by paprzyby         ###   ########.fr       */
=======
/*   By: daras <daras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/17 10:17:06 by daras            ###   ########.fr       */
>>>>>>> 8b689271f4955af3f4f028a6e5c67be4ede0c07e
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	preparing_execution(minishell_t *line)
{
<<<<<<< HEAD
	*cwd = getcwd(NULL, 0);
	if (!*cwd)
		ft_error("Error while finding the current work directory\n", NULL);
	*user_name = getenv("USER");
	if (!*user_name)
		ft_error("Error while finding the user name\n", NULL);
}

void	printing_prompt(minishell_t *line)
{
	char	*cwd;
	char	*user_name;
	char	**split_cwd;
	size_t	i;

	i = 0;
	prompt_helper(&cwd, &user_name);
	split_cwd = ft_split(cwd, '/');
	while (split_cwd[i])
		i++;
	line->prompt = malloc(ft_strlen(split_cwd[i - 1]) + 4);
	if (!line->prompt)
	{
		free(split_cwd);
		ft_error("Error while allocating memory\n", NULL);
	}
	ft_strlcpy(line->prompt, user_name, ft_strlen(user_name) + 1);
	ft_strlcat(line->prompt, " @ ", ft_strlen(line->prompt) + 4);
	ft_strlcat(line->prompt, split_cwd[i - 1], ft_strlen(line->prompt)
		+ ft_strlen(split_cwd[i - 1]) + 1);
	ft_strlcat(line->prompt, " % ", ft_strlen(line->prompt) + 4);
	line->input = readline(line->prompt);
	line->split_commands = ft_split(line->input, ' ');
	free(cwd);
=======
	if (check_builtin_commands(line))
		return ;
	path_preparation(line);
	line->path = find_path(line->split_commands[0], line);
	if (!line->path)
		ft_error("Command not found\n", NULL);
>>>>>>> 8b689271f4955af3f4f028a6e5c67be4ede0c07e
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
<<<<<<< HEAD
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_split(line->split_env);
	return (NULL);
}

void	execute_command(minishell_t *line)
{
	char	*path;

	line->env = getenv("PATH");
	if (!line->env)
		return ;
	line->split_env = ft_split(line->env, ':');
	if (!line->split_env)
		return ;
	if (check_builtin_commands(line))
		return ;
	path = find_path(line->split_commands[0], line);
	if (!path)
		ft_error("Command not found\n", NULL);
	if (execve(path, line->split_commands, NULL) == -1)
	{
		ft_error("Execution failed\n", NULL);
		free(path);
=======
>>>>>>> 8b689271f4955af3f4f028a6e5c67be4ede0c07e
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

//need to check how to exit the child process and parent procces