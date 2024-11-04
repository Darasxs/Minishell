/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:00:06 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/04 16:07:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_program_name(t_ms *ms)
{
	if (ft_strncmp(ms->split_commands[0], "./minishell", 12) == 0
		|| (ft_strncmp(ms->split_commands[0], "bash", 5) == 0))
		increment_shlvl(ms);
	if (execve(ms->split_commands[0], ms->split_commands, ms->env_copy)
		== -1)
	{
		if (errno == ENOENT)
			ms->exit_status = 127;
		else if (errno == EACCES)
			ms->exit_status = 126;
		else
			ms->exit_status = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(ms->exit_status);
	}
}
