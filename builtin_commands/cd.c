/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/16 08:12:55 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(minishell_t *line)
{
	if (!line->split_commands[1] || line->split_commands[1][0] == '~')
	{
		line->env = getenv("HOME");
		if (!line->env)
			return ;
		if (chdir(line->env) != 0)
			ft_error("Error while finding the Home directory\n", NULL);
	}
	else if (line->split_commands[1])
	{
		if (chdir(line->split_commands[1]) != 0)
			ft_error("cd: no such file or directory: ", line->split_commands[1]);
	}
	else
		ft_error("Command not found\n", NULL);
}
