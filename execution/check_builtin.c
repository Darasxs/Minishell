/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:33:06 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/28 05:23:21 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
