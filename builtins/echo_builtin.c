/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:23:28 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/18 10:14:14 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_newline(t_ms *ms, t_token *token, size_t i)
{
	while (token->value && token->value[0] == '-' && token->value[1] == 'n')
	{
		i++;
		token = token->next;
	}
	while (ms->split_commands[i + 1])
	{
		printf("%s ", ms->split_commands[i]);
		i++;
	}
	printf("%s", ms->split_commands[i]);
	return ;
}

void	print_echo_env(t_ms *ms, size_t *k, size_t *l)
{
	(*l)++;
	while (ms->env_copy[*k][*l])
	{
		printf("%c", ms->env_copy[*k][*l]);
		(*l)++;
	}
	printf(" ");
}

void	echo_env(t_ms *ms)
{
	size_t	i;
	size_t	k;
	size_t	l;

	i = 1;
	while (ms->split_commands[i] && ms->split_commands[i][0] == '$')
	{
		ms->split_commands[i] = ft_substr(ms->split_commands[i], 1,
				ft_strlen(ms->split_commands[i]) + 1);
		k = 0;
		while (ms->env_copy[k][l])
		{
			l = 0;
			while (ms->env_copy[k][l] != '=')
				l++;
			if (ft_strncmp(ms->split_commands[i], ms->env_copy[k], l - 1) == 0)
			{
				print_echo_env(ms, &k, &l);
				break ;
			}
			else
				k++;
		}
		i++;
	}
}

void	echo_builtin(t_ms *ms, t_token *token)
{
	size_t	i;

	i = 1;
	if (!ms->split_commands[i])
		printf("\n");
	else if (ft_strncmp(ms->split_commands[1], "~", 2) == 0
		&& !ms->split_commands[2])
		printf("%s\n", getenv("HOME"));
	else if (token->value[0] == '-' && token->value[1] == 'n'
		&& token->next->value)
		echo_newline(ms, token, i);
	else if (ms->split_commands[i][0] == '$')
	{
		echo_env(ms);
		printf("\n");
	}
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
