/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/04 15:45:47 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_oldpwd(t_ms *ms)
{
	int		i;
	char	*equal_pos;
	int		len;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	while (ms->env_copy[i])
	{
		equal_pos = ft_strrchr(ms->env_copy[i], '=');
		len = equal_pos - ms->env_copy[i];
		if (ft_strncmp(ft_substr(ms->env_copy[i], 0, len), "OLDPWD", len) == 0)
		{
			free(ms->env_copy[i]);
			ms->env_copy[i] = malloc(sizeof(char) * (ft_strlen(cwd) + 8));
			if (!ms->env_copy[i])
				ft_error("Error while allocating the memory\n", ms);
			ft_strlcpy(ms->env_copy[i], "OLDPWD=", 8);
			ft_strlcat(ms->env_copy[i], cwd, ft_strlen(ms->env_copy[i])
				+ ft_strlen(cwd) + 1);
			free(cwd);
			return ;
		}
		i++;
	}
}

void	update_pwd(t_ms *ms)
{
	int		i;
	char	*equal_pos;
	int		len;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	while (ms->env_copy[i])
	{
		equal_pos = ft_strrchr(ms->env_copy[i], '=');
		len = equal_pos - ms->env_copy[i];
		if (ft_strncmp(ft_substr(ms->env_copy[i], 0, len), "PWD", len) == 0)
		{
			free(ms->env_copy[i]);
			ms->env_copy[i] = malloc(sizeof(char) * (ft_strlen(cwd) + 5));
			if (!ms->env_copy[i])
				ft_error("Error while allocating the memory\n", ms);
			ft_strlcpy(ms->env_copy[i], "PWD=", 5);
			ft_strlcat(ms->env_copy[i], cwd, ft_strlen(ms->env_copy[i])
				+ ft_strlen(cwd) + 1);
			free(cwd);
			return ;
		}
		i++;
	}
}

void	cd_home(t_ms *ms)
{
	ms->env = ft_getenv("HOME", ms);
	if (!ms->env)
	{
		ms->exit_status = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exit(ms->exit_status);
	}
	if (chdir(ms->env) != 0)
	{
		ms->exit_status = 1;
		ft_putstr_fd("minishell: error while finding the HOME directory\n", 2);
		exit(ms->exit_status);
	}
	ms->first_iteration = false;
}

void	cd_builtin(t_ms *ms)
{
	if (!ms->split_commands[1] || (ms->split_commands[1][0] == '~'
		&& ms->split_commands[1][1] == '\0'))
		cd_home(ms);
	else if (ms->split_commands[1][0] == '?'
		&& ms->split_commands[1][1] == '\0')
	{
		ft_putstr_fd("minishell: cd: <: Not a directory\n", 2);
		ms->exit_status = 1;
	}
	else if (ft_strncmp("/", getcwd(NULL, 0), 2) != 0)
	{
		update_oldpwd(ms);
		if (chdir(ms->split_commands[1]) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(ms->split_commands[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			ms->exit_status = 1;
			return ;
		}
		ms->first_iteration = false;
	}
	update_pwd(ms);
}
