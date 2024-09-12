/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/12 10:44:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printing_prompt(minishell_t *line)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_error("Error while finding the current work directory\n");
	line->prompt = malloc(ft_strlen(cwd) + 4);
	if (!line->prompt)
	{
		free(cwd);
		ft_error("Error while allocating memory\n");
	}
	ft_strlcpy(line->prompt, cwd, ft_strlen(cwd) + 4);
	ft_strlcat(line->prompt, " % ", ft_strlen(line->prompt) + 4);
	line->input = readline(line->prompt);
	line->split_commands = ft_split(line->input, ' ');
	free(cwd);
}

char	*find_path(char *path, minishell_t *line)
{
	char	*full_path;
	int		i;

	i = 0;
	while (line->split_env[i])
	{
		full_path = malloc(ft_strlen(line->split_env[i]) + ft_strlen(path) + 2);
		if(!full_path)
			return(free(full_path), NULL);
		ft_strlcpy(full_path, line->split_env[i], ft_strlen(line->split_env[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, path, ft_strlen(full_path) + ft_strlen(path) + 1);
		if(access(full_path, X_OK) == 0)
		{
			free_split(line->split_env);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_split(line->split_env);
	return(NULL);
}

void	cd(minishell_t *line)
{
	if (!line->split_commands[1])
		printf("cd\n");
	else if (line->split_commands[1][1] == '.')
		printf("cd ..\n");
	else if (line->split_commands[1][0] == '.')
		printf("cd .\n");
	//functions to use:
	//chdir()
	//opendir()
	//readdir()
	//closedir()
	//execve()
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
	if (ft_strncmp(line->split_commands[0], "cd", ft_strlen(line->split_commands[0]) + 3) == 0) //case dla cd
	{
		cd(line);
		//free(path);
		return ;
	}
	path = find_path(line->split_commands[0], line);
	if (!path)
		ft_error("Command not found\n");
	if (execve(path, line->split_commands, NULL) == -1)
	{
		ft_error("Execution failed\n");
		free(path);
	}
	free(path);
}

void	minishell(minishell_t *line)
{
	pid_t	pid;

	printing_prompt(line);
	if (line->input)
	{
		add_history(line->input);
		pid = fork();
		if (pid == 0)
			execute_command(line);
		else if (pid < 0)
		{
			free_split(line->split_commands);
			ft_error("Error occured while forking\n");
		}
		else if (pid > 0)
			wait(NULL);
	}
	cleanup(line);
}
