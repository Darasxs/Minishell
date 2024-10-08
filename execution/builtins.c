/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:27:39 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/08 18:11:11 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_minishell *line)
{
	if (!line->split_commands[0])
		return ;
	else if (ft_strncmp(line->split_commands[0], "unset", 6) == 0
		&& line->split_commands[1])
		unset_builtin(line);
	else if (ft_strncmp(line->split_commands[0], "exit", 5) == 0)
		exit_builtin(line);
	else if (ft_strncmp(line->split_commands[0], "echo", 5) == 0)
		echo_builtin(line);
	else
		export_builtin(line);
}

bool	check_builtin(t_minishell *line)
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
	else if (ft_strrchr(line->split_commands[0], '=') != 0)
		return (true);
	else if (ft_strncmp(line->split_commands[0], "echo", 5) == 0)
		return (true);
	return (false);
}
