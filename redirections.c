/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:12:02 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/26 21:09:47 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(minishell_t *line)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (line->split_commands[i])
	{
		if (line->split_commands[i][j] == '>')
		{
			handle_single_output(line, i);
			j++;
		}
		else if (line->split_commands[i][j] == '>>')
		{
			handle_double_output(line, i);
			j++;
		}
		else if (line->split_commands[i][j] == '<')
		{
			handle_single_input(line, i);
			j++;
		}
		else if (line->split_commands[i][j] == '<<')
		{
			handle_double_input(line, i);
			j++;
		}
		i++;
	}
}
