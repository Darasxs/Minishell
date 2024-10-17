/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:23:28 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/17 12:10:24 by paprzyby         ###   ########.fr       */
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
	t_token	*token;

	i = 1;
	token = ms->token->next;
	if (!ms->split_commands[i])
		printf("\n");
	else if (ft_strncmp(ms->split_commands[1], "~", 2) == 0
		&& !ms->split_commands[2])
		printf("%s\n", getenv("HOME"));
	else if (token->value[0] == '-' && token->value[1] == 'n')
	{
		while (token->value[0] == '-' && token->value[1] == 'n' && token->value)
		{
			i++;
			token = token->next;
		}
		print_echo(ms, i);
	}
	else if (ms->split_commands[i][0] == '$')
		echo_env(ms);
	else
	{
		while (ms->split_commands[i] && ms->split_commands[i][0] != '>')
		{
			printf("%s ", ms->split_commands[i]);
			i++;
		}
		printf("\n");
	}
}
