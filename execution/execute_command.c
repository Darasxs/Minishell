/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:23:56 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/31 18:22:50 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *path, t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->split_env[i])
	{
		ms->full_path = malloc(ft_strlen(ms->split_env[i]) + ft_strlen(path)
				+ 2);
		if (!ms->full_path)
			return (NULL);
		ft_strlcpy(ms->full_path, ms->split_env[i], ft_strlen(ms->split_env[i])
			+ 1);
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

void	execute_command(t_ms *ms)
{
	int	j;

	if (ft_strncmp(ms->split_commands[0], "env", 3) == 0)
		env_builtin(ms);
	else if (ms->split_commands[0][0] == '.' && ms->split_commands[0][1] == '/')
		execute_program_name(ms);
	else
	{
		j = 0;
		while (ms->split_commands[j])
		{
			if (ms->split_commands[j][0] == '>'
				|| ms->split_commands[j][0] == '<')
			{
				free(ms->split_commands[j]);
				ms->split_commands[j] = NULL;
			}
			j++;
		}
		ms->env = ft_getenv("PATH", ms);
		if (!ms->env)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(ms->split_commands[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ms->exit_status = 1;
			exit(ms->exit_status);
		}
		ms->split_env = ft_split(ms->env, ':');
		if (!ms->split_env)
			return ;
		ms->path = find_path(ms->split_commands[0], ms);
		if (!ms->path && ms->split_commands[0][0] == '/')
		{
			if (execve(ms->split_commands[0], ms->split_commands, ms->env_copy) == -1)
			{
				if (errno == ENOENT)
					ms->exit_status = 127;
				else if (errno == EACCES)
					ms->exit_status = 126;
				else
					ms->exit_status = 1;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(ms->split_commands[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit(ms->exit_status);
			}
		}
		else if (!ms->path)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(ms->split_commands[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ms->exit_status = 127;
			return ;
		}
		else if (execve(ms->path, ms->split_commands, ms->env_copy) == -1)
		{
			if (errno == ENOENT)
				ms->exit_status = 127;
			else if (errno == EACCES)
				ms->exit_status = 126;
			else
				ms->exit_status = 1;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(ms->split_commands[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			ms->exit_status = 127;
			exit(ms->exit_status);
		}
		free(ms->path);
	}
}

void	execute_program_name(t_ms *ms)
{
	if (access(ms->split_commands[0], X_OK) == 0)
	{
		if (ft_strncmp(ms->split_commands[0], "./minishell", 12) == 0
			|| (ft_strncmp(ms->split_commands[0], "bash", 5) == 0))
			increment_shlvl(ms);
		if (execve(ms->split_commands[0], ms->split_commands, ms->env_copy) ==
			-1)
		{
			if (errno == ENOENT)
				ms->exit_status = 127;
			else if (errno == EACCES)
				ms->exit_status = 126;
			else
				ms->exit_status = 1;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(ms->split_commands[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(ms->exit_status);
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 127;
	}
}
