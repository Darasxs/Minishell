/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/17 17:51:00 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_builtin(minishell_t *line)
{
	if (!line->split_commands[1] || line->split_commands[1][0] == '~')
	{
		line->env = getenv("HOME");
		if (!line->env)
			return ;
		if (chdir(line->env) != 0)
			ft_error("Error while finding the Home directory\n", NULL, line);
	}
	else if (line->split_commands[1])
	{
		if (chdir(line->split_commands[1]) != 0)
			ft_error("cd: no such file or directory: ", line->split_commands[1], line);
	}
	else
		ft_error("Command not found\n", NULL, line);
}
