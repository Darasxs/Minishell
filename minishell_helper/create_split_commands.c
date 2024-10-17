/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_split_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:28:03 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/17 19:24:55 by paprzyby         ###   ########.fr       */
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

t_token	*create_split_commands(t_minishell *ms, t_token *token)
{
	int		word_count;
	int		i;

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
		if (token->next->value)
			token = token->next;
		i++;
	}
	ms->split_commands[i] = NULL;
	return (token);
}
