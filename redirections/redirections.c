/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:57:52 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/09 20:27:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirections(t_minishell *ms)
{
	size_t i;

	i = 0;
	while (ms->split_commands[i])
	{
		if (ms->split_commands[i][0] == '>' && ms->split_commands[i][1] == '>')
		{
			handle_double_output(ms, i);
		}
		else if (ms->split_commands[i][0] == '>')
		{
			handle_single_output(ms, i);
		}
		// else if (ms->split_commands[i][j] == '<'
		//	&& ms->split_commands[i][j + 1] == '<')
		//{
		//	handle_double_input(ms, i);
		//	j += 2;
		//}
		else if (ms->split_commands[i][0] == '<')
		{
			handle_single_input(ms, i);
		}
		i++;
	}
}