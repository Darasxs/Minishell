/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/29 17:46:18 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	syntax_check(t_ms *ms)
{
	int	i;

	i = 0;
	if (ms->split_commands[i][0] == '>' && ms->split_commands[i][1] == '>' && !ms->split_commands[i + 1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[i], 2);
		ft_putstr_fd(": command not found\n", 2);
		ms->exit_status = 127;
		return (false);
	}
	else if ((ms->split_commands[i][0] == '>' || ms->split_commands[i][0] == '<')
		&& (!ms->split_commands[i + 1] || ms->split_commands[i + 1][0] == '>'
			|| ms->split_commands[i + 1][0] == '<'))
	{
		if (!ms->split_commands[i + 1] || (ms->split_commands[i + 1][0] != '<'
				&& ms->split_commands[i + 1][0] != '>'))
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
				2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(ms->split_commands[i], 2);
			ft_putstr_fd("'\n", 2);
		}
		ms->exit_status = 2;
		return (false);
	}
	else if (ms->split_commands[i][0] == '|')
	{
		if (ms->split_commands[i][0] == '|' && ms->split_commands[i + 1]
			&& ms->split_commands[i + 1][0] == '|')
			ft_putstr_fd("minishell: syntax error near unexpected token '||'\n",
				2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
				2);
		ms->exit_status = 2;
		return (false);
	}
	else if (ms->split_commands[i][0] == '~')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ft_getenv("HOME", ms), 2);
		ft_putstr_fd(": is a directory\n", 2);
		ms->exit_status = 126;
		return (false);
	}
	else if (ms->split_commands[i][0] == '.' && !ms->split_commands[i][3])
	{
		if (ms->split_commands[i][1] == '.' && !ms->split_commands[i][2])
			ft_putstr_fd("minishell: ..: command not found\n", 2);
		else
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		ms->exit_status = 127;
		return (false);
	}
	return (true);
}
