/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:33:06 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/21 13:22:54 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(minishell_t *line)
{
	if (!line->split_commands[0])
		return ;
	else if (ft_strncmp(line->split_commands[0], "env", 4) == 0)
		env_builtin(line);
	else if (ft_strncmp(line->split_commands[0], "unset", 6) == 0
		&& line->split_commands[1])
		unset_builtin(line);
	else if (ft_strncmp(line->split_commands[0], "export", 7) == 0)
		export_builtin(line);
	else if (ft_strncmp(line->split_commands[0], "exit", 5) == 0)
		exit_builtin(line);
}

bool	check_env(minishell_t *line)
{
	if (line->split_commands[0] && ft_strncmp(line->split_commands[0], "env",
			3) == 0)
		return (true);
	return (false);
}

bool	check_cd(minishell_t *line)
{
	if (ft_strncmp(line->split_commands[0], "env", 4) == 0)
		return (true);
	return (false);
}

bool	check_builtin(minishell_t *line)
{
	if (!line->split_commands[0])
		return (false);
	else if (line->split_commands[0] && ft_strncmp(line->split_commands[0],
			"cd", 3) == 0)
		return (true);
	else if (ft_strncmp(line->split_commands[0], "unset", 6) == 0
		&& line->split_commands[1])
		return (true);
	else if (ft_strncmp(line->split_commands[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(line->split_commands[0], "exit", 5) == 0)
		return (true);
	else
		return (false);
}

bool	preparing_execution(minishell_t *line)
{
	path_preparation(line);
	line->path = find_path(line->split_commands[0], line);
	if (!line->path)
		ft_error("Command not found\n", NULL, line);
	return (false);
}
