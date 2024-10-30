/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/30 18:03:51 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	export_syntax_check(t_ms *ms)
{
	int	i;

	i = 0;
	if (ms->split_commands[1][i] >= '0' && ms->split_commands[1][i] <= '9')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(ms->split_commands[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		ms->exit_status = 1;
		return (false);
	}
	if (ms->split_commands[1][i] == '-')
	{
		if (i == 1 && ms->split_commands[1][i] == '-')
			ft_putstr_fd("minishell: export: --: invalid option\n", 2);
		else
			ft_putstr_fd("minishell: export: -: invalid option\n", 2);
		ft_putstr_fd("minishell: usage: export [-nf] [name[=value] ...] or export-p\n", 2);
		ms->exit_status = 2;
		return (false);
	}
	while (ms->split_commands[1][i] && ms->split_commands[1][i] != '=')
	{
		if (ms->split_commands[1][i] == '-' || ms->split_commands[1][i] == '+'
			|| ms->split_commands[1][i] == '.'
			|| ms->split_commands[1][i] == '}'
			|| ms->split_commands[1][i] == '{'
			|| ms->split_commands[1][i] == '*'
			|| ms->split_commands[1][i] == '#'
			|| ms->split_commands[1][i] == '@'
			|| ms->split_commands[1][i] == '!'
			|| ms->split_commands[1][i] == '^'
			|| ms->split_commands[1][i] == '~')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(ms->split_commands[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ms->exit_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}

bool	unset_syntax_check(t_ms *ms)
{
	int	i;

	i = 0;
	if (ms->split_commands[1][i] == '-')
	{
		if (i == 1 && ms->split_commands[1][i] == '-')
			ft_putstr_fd("minishell: export: --: invalid option\n", 2);
		else
			ft_putstr_fd("minishell: export: -: invalid option\n", 2);
		ft_putstr_fd("minishell: usage: export [-nf] [name[=value] ...] or export-p\n", 2);
		ms->exit_status = 2;
		return (false);
	}
	while (ms->split_commands[1][i])
	{
		if (ms->split_commands[1][i] == '-' || ms->split_commands[1][i] == '+'
			|| ms->split_commands[1][i] == '.'
			|| ms->split_commands[1][i] == '}'
			|| ms->split_commands[1][i] == '{'
			|| ms->split_commands[1][i] == '*'
			|| ms->split_commands[1][i] == '#'
			|| ms->split_commands[1][i] == '@'
			|| ms->split_commands[1][i] == '!'
			|| ms->split_commands[1][i] == '^'
			|| ms->split_commands[1][i] == '~'
			|| ms->split_commands[1][i] == '=')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(ms->split_commands[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ms->exit_status = 1;
			return (false);
		}
		i++;
	}
	return (true);
}

bool	syntax_check(t_ms *ms)
{
	int	i;

	if (ft_strncmp(ms->split_commands[0], "export", 7) == 0
		&& ms->split_commands[1] && !export_syntax_check(ms))
		return (false);
	if (ft_strncmp(ms->split_commands[0], "unset", 6) == 0
		&& ms->split_commands[1] && !unset_syntax_check(ms))
		return (false);
	else if (ms->split_commands[0][0] == '>' && ms->split_commands[0][1] == '>'
		&& !ms->split_commands[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ms->exit_status = 127;
		return (false);
	}
	else if ((ms->split_commands[0][0] == '>'
			|| ms->split_commands[0][0] == '<') && (!ms->split_commands[1]
			|| ms->split_commands[1][0] == '>'
			|| ms->split_commands[1][0] == '<'))
	{
		if (!ms->split_commands[1] || (ms->split_commands[1][0] != '<'
				&& ms->split_commands[1][0] != '>'))
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
				2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(ms->split_commands[0], 2);
			ft_putstr_fd("'\n", 2);
		}
		ms->exit_status = 2;
		return (false);
	}
	else if (ms->split_commands[0][0] == '|')
	{
		if (ms->split_commands[0][0] == '|' && ms->split_commands[1]
			&& ms->split_commands[1][0] == '|')
			ft_putstr_fd("minishell: syntax error near unexpected token '||'\n",
				2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token '|'\n",
				2);
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
	else if (ms->split_commands[0][0] == '.' && !ms->split_commands[0][3])
	{
		if (ms->split_commands[0][1] == '.' && !ms->split_commands[0][2])
			ft_putstr_fd("minishell: ..: command not found\n", 2);
		else
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		ms->exit_status = 127;
		return (false);
	}
	else if ((ms->split_commands[0][0] == '>'
			&& ms->split_commands[0][1] == '>')
		|| (ms->split_commands[0][0] == '>' && ms->split_commands[1]
			&& ms->split_commands[1][1] == '>'))
	{
		ms->exit_status = 0;
		return (false);
	}
	else if (ms->split_commands[0][0] == '>' || ms->split_commands[0][0] == '<')
	{
		ms->exit_status = 127;
		return (false);
	}
	else
	{
		i = 0;
		while (ms->split_commands[i])
			i++;
		i--;
		if (ms->split_commands[i][0] == '>' || ms->split_commands[i][0] == '<')
		{
			ms->exit_status = 0;
			return (false);
		}
	}
	return (true);
}
