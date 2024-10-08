/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:57:52 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/08 08:47:41 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirections(t_minishell *line)
{
	size_t i;

	i = 0;
	while (line->split_commands[i])
	{
		if (line->split_commands[i][0] == '>' && line->split_commands[i][1] == '>')
		{
			handle_double_output(line, i);
		}
		else if (line->split_commands[i][0] == '>')
		{
			handle_single_output(line, i);
		}
		// else if (line->split_commands[i][j] == '<'
		//	&& line->split_commands[i][j + 1] == '<')
		//{
		//	handle_double_input(line, i);
		//	j += 2;
		//}
		else if (line->split_commands[i][0] == '<')
		{
			handle_single_input(line, i);
		}
		i++;
	}
}