/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:23:56 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/01 13:31:37 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *path, t_minishell *line)
{
	int	i;

	i = 0;
	while (line->split_env[i])
	{
		line->full_path = malloc(ft_strlen(line->split_env[i]) + ft_strlen(path)
				+ 2);
		if (!line->full_path)
			return (free(line->full_path), NULL);
		ft_strlcpy(line->full_path, line->split_env[i],
			ft_strlen(line->split_env[i]) + 1);
		ft_strlcat(line->full_path, "/", ft_strlen(line->full_path) + 2);
		ft_strlcat(line->full_path, path, ft_strlen(line->full_path)
			+ ft_strlen(path) + 1);
		if (access(line->full_path, X_OK) == 0)
		{
			free_split(line->split_env);
			return (line->full_path);
		}
		free(line->full_path);
		line->full_path = NULL;
		i++;
	}
	free_split(line->split_env);
	return (NULL);
}

void	execute_command(t_minishell *line)
{
	line->env = getenv("PATH");
	if (!line->env)
		return ;
	line->split_env = ft_split(line->env, ':');
	if (!line->split_env)
		return ;
	line->path = find_path(line->split_commands[0], line);
	if (!line->path)
		wrong_command(line->split_commands[0], line);
	if (execve(line->path, line->split_commands, line->env_copy) == -1)
		ft_error("Execution failed\n", line);
	free(line->path);
}

void	increment_shlvl(t_minishell *line)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl;
	size_t	i;
	char	*new_env;

	i = 0;
	shlvl_str = NULL;
	while (line->env_copy[i])
	{
		if (ft_strncmp(line->env_copy[i], "SHLVL=", 6) == 0)
		{
			shlvl_str = ft_strdup(line->env_copy[i] + 6);
			break ;
		}
		i++;
	}
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
		free(shlvl_str);
		new_shlvl = ft_itoa(shlvl);
		if (new_shlvl)
		{
			new_env = malloc(strlen("SHLVL=") + strlen(new_shlvl) + 1);
			if (new_env)
			{
				ft_strlcpy(new_env, "SHLVL=", 6 + ft_strlen(new_shlvl) + 1);
				ft_strlcat(new_env, new_shlvl, 6 + ft_strlen(new_shlvl) + 1);
				free(line->env_copy[i]);
				line->env_copy[i] = new_env;
			}
			free(new_shlvl);
		}
	}
}

void	execute_program_name(t_minishell *line)
{
	if (access(line->split_commands[0], X_OK) == 0)
	{
		if (ft_strncmp(line->split_commands[0], "./minishell", 12) == 0
			|| (ft_strncmp(line->split_commands[0], "bash", 5) == 0))
			increment_shlvl(line);
		if (execve(line->split_commands[0], line->split_commands,
				line->env_copy) == -1)
		{
			if (line->split_commands[0][0] == '.'
				&& line->split_commands[0][1] == '/'
				&& line->split_commands[0][2] == '\0')
				printf("bash: ./: is a directory\n");
		}
		else
			ft_error("Execution failed.", line);
	}
	else
		printf("No such file or directory.\n");
}
