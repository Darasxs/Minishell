/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/28 01:13:42 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quots(minishell_t *line ,char **commands)
{
	size_t	quots_num;

	quots_num = 0;
	//while ()
	(void)line;
	(void)commands;
}

void	parsing(minishell_t *line ,char **commands)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	(void)commands;
	while (line->split_commands[i])
	{
		j = 0;
		if (line->split_commands[i][j] == '$' && line->split_commands[i][j
			+ 1] == '?')
		{
			handle_exit_code(line, i);
			j++;
		}
		i++;
	}
}
