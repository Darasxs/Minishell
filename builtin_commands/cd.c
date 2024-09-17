/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:54:20 by paprzyby          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/14 11:31:21 by paprzyby         ###   ########.fr       */
=======
/*   Updated: 2024/09/16 08:12:55 by dpaluszk         ###   ########.fr       */
>>>>>>> 8b689271f4955af3f4f028a6e5c67be4ede0c07e
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
