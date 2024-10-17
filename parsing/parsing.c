/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:55:55 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/16 17:55:27 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_init(t_minishell *ms)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("Error while allocating the memory\n", ms);
	token->value = NULL;
	return (token);
}

bool	is_space(t_minishell *ms)
{
	if (ms->input[ms->input_pos] == ' ')
		return (true);
	else if (ms->input[ms->input_pos] == '\t')
		return (true);
	else if (ms->input[ms->input_pos] == '\n')
		return (true);
	else if (ms->input[ms->input_pos] == '\v')
		return (true);
	else if (ms->input[ms->input_pos] == '\f')
		return (true);
	else if (ms->input[ms->input_pos] == '\r')
		return (true);
	else
		return (false);
}

t_token	*parsing(t_minishell *ms)
{
	t_token	*token;
	t_token	*head;

	token = token_init(ms);
	ms->input_len = ft_strlen(ms->input);
	head = token;
	while (ms->input_len > ms->input_pos)
	{
		if (is_space(ms))
			ms->input_pos++;
		else
		{
			get_token(ms, token);
			ms->input_pos++;
			if (token->value[0] != '|')
				ms->token_count++;
			token->next = token_init(ms);
			token = token->next;
		}
	}
	token = NULL;
	token = head;
	return (token);
}
