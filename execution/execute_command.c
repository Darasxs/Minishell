/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:23:56 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/05 14:35:40 by paprzyby         ###   ########.fr       */
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

void	execution_error(t_ms *ms, bool flag)
{
	if (flag)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ms->exit_status = 127;
	}
	exit(ms->exit_status);
}

void	set_exit_status(t_ms *ms)
{
	if (errno == ENOENT)
		ms->exit_status = 127;
	else if (errno == EACCES)
		ms->exit_status = 126;
	else
		ms->exit_status = 1;
}

void	free_redir(t_ms *ms)
{
	size_t j;

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
}

void	execute_command(t_ms *ms)
{
	if (ms->split_commands[0][0] == '.' && ms->split_commands[0][1] == '/')
		execute_program_name(ms);
	else
	{
		free_redir(ms);
		ms->env = ft_getenv("PATH", ms);
		if (!ms->env)
			execution_error(ms, true);
		ms->split_env = ft_split(ms->env, ':');
		if (!ms->split_env)
			return ;
		ms->path = find_path(ms->split_commands[0], ms);
		if (!ms->path && ms->split_commands[0][0] == '/'
			&& execve(ms->split_commands[0], ms->split_commands, ms->env_copy)
			== -1)
		{
			set_exit_status(ms);
			execution_error(ms, true);
		}
		else if (!ms->path || execve(ms->path, ms->split_commands, ms->env_copy)
			== -1)
			execution_error(ms, false);
		free(ms->path);
	}
}
