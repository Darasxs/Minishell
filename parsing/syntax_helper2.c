/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:40:23 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/05 19:41:34 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	helper3(t_ms *ms, int i)
{
	if ((ms->split_commands[i][0] == '>' || ms->split_commands[i][0] == '<')
		&& ft_strncmp(ms->split_commands[0], "echo", 5) != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(&ms->split_commands[i][0], 2);
		ft_putstr_fd("'\n", 2);
		ms->exit_status = 2;
		return (false);
	}
	return (true);
}
