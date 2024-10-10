/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:23:28 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/09 20:27:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_minishell *ms, size_t i)
{
	while (ms->split_commands[i + 1])
	{
		printf("%s ", ms->split_commands[i]);
		i++;
	}
	printf("%s", ms->split_commands[i]);
	return ;
}

void	echo_env(t_minishell *ms)
{
	size_t	i;
	size_t	k;
	size_t	l;

	i = 1;
	while (ms->split_commands[i] && ms->split_commands[i][0] == '$')
	{
		ms->split_commands[i] = ft_substr(ms->split_commands[i], 1, ft_strlen(ms->split_commands[i]) + 1);
		k = 0;
		while (ms->env_copy[k][l])
		{
			l = 0;
			while (ms->env_copy[k][l] != '=')
				l++;
			if (ft_strncmp(ms->split_commands[i], ms->env_copy[k], l - 1) == 0)
			{
				l++;
				while (ms->env_copy[k][l])
				{
					printf("%c", ms->env_copy[k][l]);
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

void	echo_builtin(t_minishell *ms)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (!ms->split_commands[i])
		printf("\n");
	else if (ft_strncmp(ms->split_commands[1], "~", 2) == 0
		&& !ms->split_commands[2])
		printf("%s\n", getenv("HOME"));
	else if (ms->split_commands[i][0] == '-'
		&& ms->split_commands[i][1] == 'n')
	{
		j = 0;
		while (ms->split_commands[i][j] == '-'
			|| ms->split_commands[i][j] == 'n')
			j++;
		if (!ms->split_commands[i][j])
			print_echo(ms, i + 1);
		i++;
	}
	else if (ms->apos_check == true)
		printf("%s\n", ms->split_commands[1]);
	else if (ms->split_commands[i][0] == '$')
		echo_env(ms);
	else
	{
		i = 1;
		while (ms->split_commands[i])
		{
			printf("%s ", ms->split_commands[i]);
			i++;
		}
		printf("\n");
	}
}
