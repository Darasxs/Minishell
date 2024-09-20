/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/20 18:27:48 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_builtin(minishell_t *line)
{
	if (!line->split_commands[1] || (line->split_commands[1][0] == '~' && line->split_commands[1][1] == '\0'))
	{
		line->env = getenv("HOME");
		if (!line->env)
			ft_error("cd: HOME not set", NULL, line);
		if (chdir(line->env) != 0)
			ft_error("Error while finding the HOME directory\n", NULL, line);
	}
	else if (line->split_commands[1][0] == '-' && line->split_commands[1][1] == '\0')
	{
		line->env = getenv("OLDPWD");
		if (!line->env)
			ft_error("cd: OLDPWD not set", NULL, line);
		if (chdir(line->env) != 0)
			ft_error("Error while finding the previous working directory\n", NULL, line);
		printf("%s\n", line->env);
	}
	else if (line->split_commands[1])
	{
		if (chdir(line->split_commands[1]) != 0)
			ft_error("cd: no such file or directory: ", line->split_commands[1], line);
	}
	else
		ft_error("Command not found\n", NULL, line);
}
