/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/06 18:00:06 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	export_syntax_check(t_ms *ms)
{
	int	i;

	i = 0;
	if (ms->split_commands[1][i] >= '0' && ms->split_commands[1][i] <= '9')
		return (export_error(ms, true), false);
	if (ms->split_commands[1][i] == '-')
		return (export_error(ms, true), false);
	while (ms->split_commands[1][i] && ms->split_commands[1][i] != '=')
	{
		if (!export_helper(ms, i))
			return (export_error(ms, true), false);
		i++;
	}
	i = 1;
	while (ms->split_commands[i])
	{
		if ((ms->split_commands[i][0] >= '0' && ms->split_commands[i][0] <= '9')
			|| ms->split_commands[i][0] == '=')
			return (export_error(ms, true), false);
		else if (ms->split_commands[i][0] == '-')
			return (export_error(ms, false), false);
		i++;
	}
	return (true);
}

bool	unset_syntax_check(t_ms *ms)
{
	int	i;

	i = 0;
	if (ms->split_commands[1] && (ms->split_commands[1][0] == '\0'
		|| ms->split_commands[1][0] == '='
		|| ms->split_commands[1][0] == '$'))
	{
		ft_putstr_fd("minishell: unset: `<': not a valid identifier\n", 2);
		ft_putstr_fd("minishell: unset: `>': not a valid identifier\n", 2);
		ms->exit_status = 1;
		return (false);
	}
	else if (ms->split_commands[1] && ms->split_commands[1][0] == '?'
		&& ms->split_commands[1][1] == '\0')
		return (unset_error(ms, true), false);
	else if (ms->split_commands[1][i] == '-')
		return (unset_error(ms, false), false);
	while (ms->split_commands[1][i])
	{
		if (!unset_helper(ms, i))
			return (unset_error(ms, true), false);
		i++;
	}
	return (true);
}

void	syntax_execution_error(t_ms *ms, bool flag)
{
	if (flag)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ms->exit_status = 127;
	}
}

bool	helper2(t_ms *ms)
{
	if ((ms->split_commands[0][0] == '>' || ms->split_commands[0][0] == '<'
			|| ms->split_commands[0][0] == '|') && (!ms->split_commands[1]
			|| ms->split_commands[1][0] == '>'
			|| ms->split_commands[1][0] == '<'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd("'\n", 2);
		ms->exit_status = 2;
		return (false);
	}
	else if (ms->split_commands[0][0] == '~')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ft_getenv("HOME", ms), 2);
		ft_putstr_fd(": is a directory\n", 2);
		ms->exit_status = 126;
		return (false);
	}
	return (true);
}

bool	syntax_check(t_ms *ms)
{
	if (ft_strncmp(ms->split_commands[0], "export", 7) == 0
		&& ms->split_commands[1] && !export_syntax_check(ms))
		return (false);
	if (ft_strncmp(ms->split_commands[0], "unset", 6) == 0
		&& ms->split_commands[1] && !unset_syntax_check(ms))
		return (false);
	else if (ms->split_commands[0][0] == '>' && ms->split_commands[0][1] == '>'
		&& !ms->split_commands[1])
		return (syntax_execution_error(ms, false), false);
	else if (!helper2(ms))
		return (false);
	else if (ms->split_commands[0][0] == '.' && !ms->split_commands[0][3])
		return (syntax_execution_error(ms, false), false);
	else if ((ms->split_commands[0][0] == '>'
		&& ms->split_commands[0][1] == '>')
		|| (ms->split_commands[0][0] == '>' && ms->split_commands[1]
		&& ms->split_commands[1][1] == '>'))
		return (syntax_execution_error(ms, false), false);
	return (true);
}
