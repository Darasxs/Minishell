/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 01:57:04 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 05:25:28 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_loop()
{
	while (1)
		readline("> ");
}

void	skip_quotes(t_minishell *line)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	end;

	i = 0;
	while (line->split_commands[i])
	{
		j = 0;
		if (line->split_commands[i][j])
		{
			while (line->split_commands[i][j] == 39 || line->split_commands[i][j] == 34)
				j++;
			start = j;
			while (line->split_commands[i][j] != 39 && line->split_commands[i][j] != 34 && line->split_commands[i][j])
				j++;
			end = j + 1;
			ft_strlcpy(line->split_commands[i], line->split_commands[i] + start, end - start);
		}
		i++;
	}
}

void	handle_quotes(t_minishell *line)
{
	size_t	quots_count;
	size_t	apos_count;
	size_t	i;
	size_t	j;

	i = 0;
	while (line->split_commands[i])
	{
		quots_count = 0;
		apos_count = 0;
		j = 0;
		while (line->split_commands[i][j])
		{
			if (line->split_commands[i][j] == 39)
				quots_count++;
			else if (line->split_commands[i][j] == 34)
				apos_count++;
			j++;
		}
		if (quots_count % 2 != 0 || apos_count % 2 != 0)
			quotes_loop();
		i++;
	}
	skip_quotes(line);
}
