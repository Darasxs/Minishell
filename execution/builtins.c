/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:27:39 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/23 16:54:47 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_ms *ms)
{
	if (!ms->split_commands[0])
		return ;
	else if (ft_strncmp(ms->split_commands[0], "unset", 6) == 0
		&& ms->split_commands[1])
		unset_builtin(ms);
	else if (ft_strncmp(ms->split_commands[0], "exit", 5) == 0)
		exit_builtin(ms);
	else if (ft_strncmp(ms->split_commands[0], "echo", 5) == 0)
		echo_builtin(ms, ms->token->next);
	else if (ft_strncmp(ms->split_commands[0], "pwd", 4) == 0)
		pwd_builtin(ms);
	else
		export_builtin(ms);
}

bool	check_builtin(t_ms *ms)
{
	if (!ms->split_commands[0])
		return (false);
	else if (ft_strncmp(ms->split_commands[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "unset", 6) == 0
		&& ms->split_commands[1])
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "exit", 5) == 0)
		return (true);
	else if (ft_strrchr(ms->split_commands[0], '=') != 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(ms->split_commands[0], "pwd", 4) == 0)
		return (true);
	return (false);
}
