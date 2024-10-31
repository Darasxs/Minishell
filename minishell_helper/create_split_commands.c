/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_split_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:28:03 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/31 18:18:47 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_split_size(t_token *token)
{
	int	word_count;

	word_count = 0;
	while (token->value && token->value[0] != '|')
	{
		word_count++;
		token = token->next;
	}
	return (word_count);
}

void	remove_quotes(t_ms *ms, int split)
{
	int		i;
	int		len;
	char	*new_command;

	i = 0;
	len = 0;
	while (ms->split_commands[split][i])
	{
		if (ms->split_commands[split][i] != '\"'
			|| ms->split_commands[split][i] != '\'')
			len++;
		i++;
	}
	i = 0;
	new_command = malloc(sizeof(char) * (len + 1));
	if (!new_command)
		ft_error("Error while allocating the memory for new_env\n", ms);
	len = 0;
	while (ms->split_commands[split][i])
	{
		if (ms->split_commands[split][i] != '\"'
			&& ms->split_commands[split][i] != '\'')
		{
			new_command[len] = ms->split_commands[split][i];
			len++;
		}
		i++;
	}
	free(ms->split_commands[split]);
	new_command[len] = '\0';
	ms->split_commands[split] = new_command;
}

t_token	*create_split_commands(t_ms *ms, t_token *token)
{
	int	word_count;
	int	i;

	if (token->value[0] == '|')
		token = token->next;
	word_count = count_split_size(token);
	ms->split_commands = malloc(sizeof(char *) * (word_count + 1));
	if (!ms->split_commands)
		ft_error("Error while allocating the memory\n", ms);
	i = 0;
	while (i < word_count)
	{
		ms->split_commands[i] = ft_strdup(token->value);
		remove_quotes(ms, i);
		if (token->next->value)
			token = token->next;
		i++;
	}
	ms->split_commands[i] = NULL;
	return (token);
}
