/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:23:56 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 01:24:16 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	line->env = getenv("PATH");
	if (!line->env)
		return ;
	line->split_env = ft_split(line->env, ':');
	if (!line->split_env)
		return ;
	line->path = find_path(line->split_commands[0], line);
	if (!line->path)
		ft_error("Command not found\n", NULL, line);
	if (execve(line->path, line->split_commands, line->env_copy) == -1)
		ft_error("Execution failed.\n", NULL, line);
	free(line->path);
}
