/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:57:52 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/28 19:43:39 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_if_redirections(t_ms *ms)
{
	size_t	i;

	i = 0;
	while (ms->split_commands[i])
	{
		if (ms->split_commands[i][0] == '>' && ms->split_commands[i][1] == '>')
			return (true);
		else if (ms->split_commands[i][0] == '>')
			return (true);
		else if (ms->split_commands[i][0] == '<'
			&& ms->split_commands[i][1] == '<')
			return (true);
		else if (ms->split_commands[i][0] == '<')
			return (true);
		i++;
	}
	return (false);
}

void	handle_redirections(t_ms *ms)
{
	size_t	i;

	i = 0;
	while (ms->split_commands[i])
	{
		if (ms->split_commands[i][0] == '<' && ms->split_commands[i][1] == '<')
			handle_double_input(ms, i);
		else if (ms->split_commands[i][0] == '<')
			handle_single_input(ms, i);
		else if (ms->split_commands[i][0] == '>'
			&& ms->split_commands[i][1] == '>')
			handle_double_output(ms, i);
		else if (ms->split_commands[i][0] == '>')
			handle_single_output(ms, i);
		i++;
	}
}