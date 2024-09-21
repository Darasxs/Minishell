/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/21 19:43:14 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(minishell_t *line)
{
	size_t	i;
	char	**commands;
	int		status;
	int		input_fd;

	i = 0;
	input_fd = STDIN_FILENO;
	printing_prompt(line);
	if (line->input)
	{
		add_history(line->input);
		commands = ft_split(line->input, '|');
		while (commands[i])
		{
			execute_pipe_commands(line, commands, i, &input_fd);
			i++;
		}
		while (waitpid(-1, &status, 0) > 0)
			;
		free_split(commands);
	}
}
