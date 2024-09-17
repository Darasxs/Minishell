/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:33:06 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/17 17:51:12 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_builtin(minishell_t *line)
{
	if (!line->split_commands[0])
		return (false);
	else if (ft_strncmp(line->split_commands[0], "cd", 3) == 0)
	{
		cd_builtin(line);
		return (true);
	}
	else if (ft_strncmp(line->split_commands[0], "env", 4) == 0)
	{
		env_builtin(line);
		return (true);
	}
	else if (ft_strncmp(line->split_commands[0], "unset", 6) == 0 && line->split_commands[1])
	{
		unset_builtin(line);
		return (true);
	}
	else if (ft_strncmp(line->split_commands[0], "export", 7) == 0)
	{
		export_builtin(line);
		return (true);
	}
	else
		return (false);
}

bool	preparing_execution(minishell_t *line)
{
	if (check_builtin(line))
		return (true);
	path_preparation(line);
	line->path = find_path(line->split_commands[0], line);
	if (!line->path)
		ft_error("Command not found\n", NULL, line);
	return (false);
}
