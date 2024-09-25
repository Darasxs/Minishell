/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/25 11:03:01 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(minishell_t *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while(line->split_commands[i])
	{
		j = 0;
		if(line->split_commands[i][j] == '$' && line->split_commands[i][j+1] == '?')
		{
			handle_exit_code(line, i);
			j++;
		}
		i++;
	}
}
