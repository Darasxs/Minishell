/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:37:01 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 05:25:11 by paprzyby         ###   ########.fr       */
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
