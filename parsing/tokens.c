/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:56:13 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/31 18:21:06 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_word_token(t_ms *ms, t_token *token)
{
	int	start;

	start = ms->input_pos;
	ms->double_q = 0;
	ms->single_q = 0;
	while (ms->input[ms->input_pos])
	{
		if (ms->input[ms->input_pos] == '\'')
			ms->single_q++;
		else if (ms->input[ms->input_pos] == '\"')
			ms->double_q++;
		else if (is_space(ms) && ms->double_q % 2 == 0 && ms->single_q % 2 == 0)
			break ;
		ms->input_pos++;
	}
	if (ms->single_q % 2 != 0 || ms->double_q % 2 != 0)
	{
		ft_putstr_fd("minishell: invalid syntax\n", 2);
		return (1);
	}
	else
		token->value = ft_substr(ms->input, start, ms->input_pos - start);
	return (0);
}

int	get_token(t_ms *ms, t_token *token)
{
	if (ms->input[ms->input_pos] == '|')
		token->value = ft_strdup("|");
	else if (ms->input[ms->input_pos + 1] == '<'
		&& ms->input[ms->input_pos] == '<')
	{
		token->value = ft_strdup("<<");
		ms->input_pos++;
	}
	else if (ms->input[ms->input_pos] == '<')
		token->value = ft_strdup("<");
	else if (ms->input[ms->input_pos + 1] == '>'
		&& ms->input[ms->input_pos] == '>')
	{
		token->value = ft_strdup(">>");
		ms->input_pos++;
	}
	else if (ms->input[ms->input_pos] == '>')
		token->value = ft_strdup(">");
	else
	{
		if (get_word_token(ms, token))
			return (1);
	}
	return (0);
}
