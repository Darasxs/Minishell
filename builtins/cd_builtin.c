/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/08 17:25:04 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_builtin(t_minishell *line)
{
	if (!line->split_commands[1] || (line->split_commands[1][0] == '~'
			&& line->split_commands[1][1] == '\0'))
	{
		line->env = getenv("HOME");
		if (!line->env)
			ft_error("minishell: cd: HOME not set\n", line);
		if (chdir(line->env) != 0)
			ft_error("minishell: error while finding the HOME directory\n", line);
	}
	else if (line->split_commands[1][0] == '-'
		&& line->split_commands[1][1] == '\0')
	{
		line->env = getenv("OLDPWD");
		if (!line->env)
			ft_error("minishell: cd: OLDPWD not set\n", line);
		if (chdir(line->env) != 0)
			ft_error("minishell: error while finding the previous working directory\n", line);
		printf("%s\n", line->env);
	}
	else
	{
		if (chdir(line->split_commands[1]) != 0)
			printf("minishell: cd: %s: No such file or directory\n", line->split_commands[1]);
	}
}
