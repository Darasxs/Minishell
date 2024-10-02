/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:57:52 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/02 16:58:43 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(t_minishell *line)
{
	size_t i;
	size_t j;

	i = 0;
	while (line->split_commands[i])
	{
		j = 0;
		while (line->split_commands[i][j])
		{
			if (line->split_commands[i][j] == '>' && line->split_commands[i][j
				+ 1] == '>')
			{
				handle_double_output(line, i);
				j += 2;
			}
			else if (line->split_commands[i][j] == '>')
			{
				handle_single_output(line, i);
				j++;
			}
			else if (line->split_commands[i][j] == '<'
				&& line->split_commands[i][j + 1] == '<')
			{
				handle_double_input(line, i);
				j += 2;
			}
			else if (line->split_commands[i][j] == '<')
			{
				handle_single_input(line, i);
				j++;
			}
		}
		i++;
	}
}
