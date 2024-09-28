/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/28 05:25:24 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quotes(t_minishell *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (line->split_commands[i])
	{
		j = 0;
		while (line->split_commands[i][j])
		{
			if (line->split_commands[i][j] == 39 || line->split_commands[i][j] == 34)
				handle_quotes(line);
			j++;
		}
		i++;
	}
}

void	check_exit_code(t_minishell *line)
{
	size_t	i;

	i = 0;
	while (line->split_commands[i])
	{
		if (line->split_commands[i][0] == '$' && line->split_commands[i][1] == '?')
			handle_exit_code(line, i);
		i++;
	}
}

void	check_redirections(t_minishell *line)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	//printf("redirection\n");
	while (line->split_commands[i])
	{
		//if (line->split_commands[i][j] == '>')
		//{
		//	handle_single_output(line, i);
		//	j++;
		//}
		//else if (line->split_commands[i][j] == '>>')
		//{
		//	handle_double_output(line, i);
		//	j++;
		//}
		//else if (line->split_commands[i][j] == '<')
		//{
		//	handle_single_input(line, i);
		//	j++;
		//}
		//else if (line->split_commands[i][j] == '<<')
		//{
		//	handle_double_input(line, i);
		//	j++;
		//}
		i++;
	}
}

void	parsing(t_minishell *line ,char **commands)
{
	(void)commands;
	check_quotes(line);
	check_exit_code(line);
	check_redirections(line);
}
