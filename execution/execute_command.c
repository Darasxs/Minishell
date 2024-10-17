/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:23:56 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/17 15:26:35 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *path, t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->split_env[i])
	{
		ms->full_path = malloc(ft_strlen(ms->split_env[i]) + ft_strlen(path)
				+ 2);
		if (!ms->full_path)
			return (free(ms->full_path), NULL);
		ft_strlcpy(ms->full_path, ms->split_env[i],
			ft_strlen(ms->split_env[i]) + 1);
		ft_strlcat(ms->full_path, "/", ft_strlen(ms->full_path) + 2);
		ft_strlcat(ms->full_path, path, ft_strlen(ms->full_path)
			+ ft_strlen(path) + 1);
		if (access(ms->full_path, X_OK) == 0)
		{
			free_split(ms->split_env);
			return (ms->full_path);
		}
		free(ms->full_path);
		ms->full_path = NULL;
		i++;
	}
	free_split(ms->split_env);
	return (NULL);
}

void	execute_command(t_minishell *ms)
{
	if (ft_strncmp(ms->split_commands[0], "env", 3) == 0)
		env_builtin(ms);
	else if (ms->split_commands[0][0] == '.' && ms->split_commands[1][1] == '/')
		execute_program_name(ms);
	else
	{
		int	j = 0;
		while (ms->split_commands[j])
		{
			if (ms->split_commands[j][0] == '>' || ms->split_commands[j][0] == '<')
			{
				free(ms->split_commands[j]);
				ms->split_commands[j] = NULL;
			}
			j++;
		}
		ms->env = getenv("PATH");
		if (!ms->env)
			return ;
		ms->split_env = ft_split(ms->env, ':');
		if (!ms->split_env)
			return ;
		ms->path = find_path(ms->split_commands[0], ms);
		if (!ms->path)
			wrong_command(ms->split_commands[0], ms);
		if (execve(ms->path, ms->split_commands, ms->env_copy) == -1)
			ft_error("Execution failed\n", ms);
		free(ms->path);
	}
}

void	increment_shlvl(t_minishell *ms)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl;
	size_t	i;
	char	*new_env;

	i = 0;
	shlvl_str = NULL;
	while (ms->env_copy[i])
	{
		if (ft_strncmp(ms->env_copy[i], "SHLVL=", 6) == 0)
		{
			shlvl_str = ft_strdup(ms->env_copy[i] + 6);
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
				free(ms->env_copy[i]);
				ms->env_copy[i] = new_env;
			}
			free(new_shlvl);
		}
	}
}

void	execute_program_name(t_minishell *ms)
{
	if (access(ms->split_commands[0], X_OK) == 0)
	{
		if (ft_strncmp(ms->split_commands[0], "./minishell", 12) == 0
			|| (ft_strncmp(ms->split_commands[0], "bash", 5) == 0))
			increment_shlvl(ms);
		if (execve(ms->split_commands[0], ms->split_commands,
				ms->env_copy) == -1)
		{
			if (ms->split_commands[0][0] == '.'
				&& ms->split_commands[0][1] == '/'
				&& ms->split_commands[0][2] == '\0')
				printf("bash: ./: is a directory\n");
		}
		else
			ft_error("Execution failed.", ms);
	}
	else
		printf("No such file or directory.\n");
}
