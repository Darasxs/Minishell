/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_split_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:06:32 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/12 17:27:13 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(t_token *token)
{
	int		pipes_count;

	pipes_count = 1;
	while (token->value)
	{
		if (token->value[0] == '|')
			pipes_count++;
		token = token->next;
	}
	return (pipes_count);
}

int	count_pipe_len(t_token *token)
{
	int		len;
	int		i;

	len = 0;
	while (token->value[0] != '|' && token->value)
	{
		i = 0;
		while (token->value[i])
		{
			i++;
			len++;
		}
		if (!token->next->value)
			return (len);
		else if (token->next->value[0] != '|')
			len++;
		token = token->next;
	}
	return (len);
}

void	join_pipes(t_minishell *ms, t_token *token, int i)
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
		if (token->next)
			ft_strlcat(ms->split_pipes[i], " ",
				ft_strlen(ms->split_pipes[i]) + 2);
		token = token->next;
	}
}

void	create_split_pipes(t_minishell *ms, t_token *token)
{
	t_token	*head;
	int		i;
	int		pipes_count;
	int		len;

	head = token;
	pipes_count = count_pipes(head);
	ms->split_pipes = malloc(sizeof(char *) * (pipes_count + 1));
	if (!ms->split_pipes)
		ft_error("Error while allocating the memory\n", ms);
	i = 0;
	len = 0;
	while (i < pipes_count && token->value)
	{
		if (token->value[0] != '|')
		{
			join_pipes(ms, token, i);
			i++;
		}
		token = token->next;
	}
	ms->split_pipes[i] = NULL;
	token = head;
}
