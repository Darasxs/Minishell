/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/11 17:19:45 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_builtin(t_minishell *ms, t_token *token)
{
	(void)token;
	if (!ms->split_commands[1] || (ms->split_commands[1][0] == '~'
			&& ms->split_commands[1][1] == '\0'))
	{
		ms->env = getenv("HOME");
		if (!ms->env)
			ft_error("minishell: cd: HOME not set\n", ms);
		if (chdir(ms->env) != 0)
			ft_error("minishell: error while finding the HOME directory\n", ms);
	}
	else if (ms->split_commands[1][0] == '-'
		&& ms->split_commands[1][1] == '\0')
	{
		ms->env = getenv("OLDPWD");
		if (!ms->env)
			ft_error("minishell: cd: OLDPWD not set\n", ms);
		if (chdir(ms->env) != 0)
			ft_error("minishell: error while finding the previous working directory\n", ms);
		printf("%s\n", ms->env);
	}
	else
	{
		if (chdir(ms->split_commands[1]) != 0)
			printf("minishell: cd: %s: No such file or directory\n", ms->split_commands[1]);
	}
}
