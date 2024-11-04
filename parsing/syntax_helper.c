/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:52:24 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/04 20:05:23 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	export_helper(t_ms *ms, int i)
{
	if (ms->split_commands[1][i] == '-' || ms->split_commands[1][i] == '+'
		|| ms->split_commands[1][i] == '.' || ms->split_commands[1][i] == '}'
		|| ms->split_commands[1][i] == '{' || ms->split_commands[1][i] == '*'
		|| ms->split_commands[1][i] == '#' || ms->split_commands[1][i] == '@'
		|| ms->split_commands[1][i] == '!' || ms->split_commands[1][i] == '^'
		|| ms->split_commands[1][i] == '~'
		|| ms->split_commands[1][i] == '\\')
		return (false);
	else
		return (true);
}

bool	unset_helper(t_ms *ms, int i)
{
	if (ms->split_commands[1][i] == '-' || ms->split_commands[1][i] == '+'
		|| ms->split_commands[1][i] == '.' || ms->split_commands[1][i] == '}'
		|| ms->split_commands[1][i] == '{' || ms->split_commands[1][i] == '*'
		|| ms->split_commands[1][i] == '#' || ms->split_commands[1][i] == '@'
		|| ms->split_commands[1][i] == '!' || ms->split_commands[1][i] == '^'
		|| ms->split_commands[1][i] == '~' || ms->split_commands[1][i] == '=')
		return (false);
	else
		return (true);
}

void	export_error(t_ms *ms, bool flag)
{
	if (flag)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(ms->split_commands[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		ms->exit_status = 1;
		return ;
	}
	ft_putstr_fd("minishell: export: -: invalid option\n", 2);
	ft_putstr_fd("export: usage: export ", 2);
	ft_putstr_fd("[-nf] [name[=value] ...] or export-p\n", 2);
	ms->exit_status = 2;
}

void	unset_error(t_ms *ms, bool flag)
{
	if (flag)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(ms->split_commands[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		ms->exit_status = 1;
		return ;
	}
	ft_putstr_fd("minishell: usage: unset ", 2);
	ft_putstr_fd("[-nf] [name[=value] ...] or unset-p\n", 2);
	ms->exit_status = 2;
}
