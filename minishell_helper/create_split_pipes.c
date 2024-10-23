/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_split_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:06:32 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/23 17:00:03 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_token *token)
{
	int		pipes_count;
	t_token	*head;

	pipes_count = 1;
	head = token;
	while (token->value)
	{
		if (token->value[0] == '|')
			pipes_count++;
		token = token->next;
	}
	token = head;
	return (pipes_count);
}

int	count_pipe_len(t_token *token)
{
	int		len;
	int		i;
	t_token	*head;

	len = 0;
	head = token;
	while (token->value[0] != '|' && token->value)
	{
		i = 0;
		while (token->value[i])
		{
			i++;
			len++;
		}
		if (!token->next->value)
		{
			token = head;
			return (len);
		}
		else if (token->next->value[0] != '|')
			len++;
		token = token->next;
	}
	token = head;
	return (len);
}

t_token	*join_pipes(t_ms *ms, t_token *token, int i)
{
	int	len;

	len = count_pipe_len(token);
	ms->split_pipes[i] = malloc(sizeof(char) * (len + 1));
	if (!ms->split_pipes[i])
		ft_error("Error while allocating the memory\n", ms);
	while (token->value && token->value[0] != '|')
	{
		ft_strlcat(ms->split_pipes[i], token->value,
			ft_strlen(token->value) + ft_strlen(ms->split_pipes[i])
			+ 1);
		if (token->next->value && token->next->value[0] != '|')
			ft_strlcat(ms->split_pipes[i], " ",
				ft_strlen(ms->split_pipes[i]) + 2);
		token = token->next;
	}
	return (token);
}

void	create_split_pipes(t_ms *ms, t_token *token)
{
	t_token	*head;
	int		i;
	int		pipes_count;

	head = token;
	pipes_count = count_pipes(head);
	ms->split_pipes = malloc(sizeof(char *) * (pipes_count + 1));
	if (!ms->split_pipes)
		ft_error("Error while allocating the memory\n", ms);
	i = 0;
	while (i < pipes_count && token->value)
	{
		if (token->value[0] != '|')
		{
			token = join_pipes(ms, token, i);
			i++;
		}
		else
			token = token->next;
	}
	ms->split_pipes[i] = NULL;
	token = head;
}
