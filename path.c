/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daras <daras@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:30:21 by daras             #+#    #+#             */
/*   Updated: 2024/09/16 15:37:01 by daras            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_preparation(minishell_t *line)
{
	line->env = getenv("PATH");
	if (!line->env)
		return ;
	line->split_env = ft_split(line->env, ':');
	if (!line->split_env)
		return ;
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
