/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/18 10:14:14 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_home(t_ms *ms)
{
	ms->env = getenv("HOME");
	if (!ms->env)
		ft_error("minishell: cd: HOME not set\n", ms);
	if (chdir(ms->env) != 0)
		ft_error("minishell: error while finding the HOME directory\n", ms);
}

void	cd_oldpwd(t_ms *ms)
{
	ms->env = getenv("OLDPWD");
	if (!ms->env)
		ft_error("minishell: cd: OLDPWD not set\n", ms);
	if (chdir(ms->env) != 0)
		ft_error("minishell: error with the previous working directory\n",
			ms);
	printf("%s\n", ms->env);
}

void	cd_builtin(t_ms *ms)
{
	if (!ms->split_commands[1] || (ms->split_commands[1][0] == '~'
		&& ms->split_commands[1][1] == '\0'))
		cd_home(ms);
	else if (ms->split_commands[1][0] == '-'
		&& ms->split_commands[1][1] == '\0')
		cd_oldpwd(ms);
	else if (ms->split_commands[1][0] == '?'
		&& ms->split_commands[1][1] == '\0')
		printf("minishell: cd: <: Not a directory\n");
	else
	{
		if (chdir(ms->split_commands[1]) != 0)
			printf("minishell: cd: %s: No such file or directory\n",
				ms->split_commands[1]);
	}
}
