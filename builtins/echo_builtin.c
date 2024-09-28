/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:23:28 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 05:24:31 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_minishell *line, size_t i)
{
	while (line->split_commands[i + 1])
	{
		printf("%s ", line->split_commands[i]);
		i++;
	}
	printf("%s", line->split_commands[i]);
	return ;
}

void	echo_builtin(t_minishell *line)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (ft_strncmp(line->split_commands[1], "~", 2) == 0
		&& !line->split_commands[2])
		printf("%s\n", getenv("HOME"));
	else if (line->split_commands[i][0] == '-'
		&& line->split_commands[i][1] == 'n')
	{
		j = 0;
		while (line->split_commands[i][j] == '-'
			|| line->split_commands[i][j] == 'n')
			j++;
		if (!line->split_commands[i][j])
			print_echo(line, i + 1);
		i++;
	}
	else
	{
		i = 1;
		while (line->split_commands[i])
		{
			printf("%s ", line->split_commands[i]);
			i++;
		}
		printf("\n");
	}
}
