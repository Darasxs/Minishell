/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:23:28 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/01 13:34:32 by paprzyby         ###   ########.fr       */
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

void	echo_env(t_minishell *line)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = 1;
	while (line->split_commands[i] && line->split_commands[i][0] == '$')
	{
		j = 1;
		line->split_commands[i] = ft_substr(line->split_commands[i], 1, ft_strlen(line->split_commands[i]) + 1);
		k = 0;
		while (line->env_copy[k][l])
		{
			l = 0;
			while (line->env_copy[k][l] != '=')
				l++;
			if (ft_strncmp(line->split_commands[i], line->env_copy[k], l - 1) == 0)
			{
				l++;
				while (line->env_copy[k][l])
				{
					printf("%c", line->env_copy[k][l]);
					l++;
				}
				printf(" ");
				break ;
			}
			else
				k++;
		}
		i++;
	}
	printf("\n");
}

void	echo_builtin(t_minishell *line)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (!line->split_commands[i])
		printf("\n");
	else if (ft_strncmp(line->split_commands[1], "~", 2) == 0
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
	else if (line->apos_check == true)
		printf("%s\n", line->split_commands[1]);
	else if (line->split_commands[i][0] == '$')
		echo_env(line);
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
