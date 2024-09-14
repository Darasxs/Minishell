/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/14 11:23:39 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_helper(char **cwd, char **user_name)
{
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
}

char	*find_path(char *path, minishell_t *line)
{
	char	*full_path;
	int		i;

	i = 0;
	while (line->split_env[i])
	{
		full_path = malloc(ft_strlen(line->split_env[i]) + ft_strlen(path) + 2);
		if (!full_path)
			return (free(full_path), NULL);
		ft_strlcpy(full_path, line->split_env[i], ft_strlen(line->split_env[i])
			+ 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, path, ft_strlen(full_path) + ft_strlen(path) + 1);
		if (access(full_path, X_OK) == 0)
		{
			free_split(line->split_env);
			return (full_path);
		}
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
			ft_error("Error occured while forking\n", NULL);
		}
		else if (pid > 0)
			wait(NULL);
	}
	cleanup(line);
}
