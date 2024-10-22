/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:56:13 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/22 16:05:10 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_quotes(t_ms *ms)
{
	if (ms->input[ms->input_pos] == '\'')
		ms->single_q++;
	else if (ms->input[ms->input_pos] == '\"')
		ms->double_q++;
}

void	get_word_token(t_ms *ms, t_token *token)
{
	int	start;

	start = ms->input_pos;
	ms->double_q = 0;
	ms->single_q = 0;
	while (ms->input[ms->input_pos])
	{
		if (ms->input[ms->input_pos] == '\''
			|| ms->input[ms->input_pos] == '\"')
			count_quotes(ms);
		if (ms->single_q == 2 || ms->double_q == 2)
			break ;
		if ((is_space(ms) || ms->input[ms->input_pos] == '|'
				|| ms->input[ms->input_pos] == '<'
				|| ms->input[ms->input_pos] == '>') && (ms->single_q % 2 == 0
				&& ms->double_q % 2 == 0))
			break ;
		ms->input_pos++;
	}
	if (ms->single_q % 2 != 0 || ms->double_q % 2 != 0)
	{
		while (1)
			readline("> ");
	}
	else
	{
		if (ms->input[start] == '\'' || ms->input[start] == '\"')
			start++;
		if (ms->input[ms->input_pos - start] == '\'' || ms->input[ms->input_pos
				- start] == '\"')
			token->value = ft_substr(ms->input, start, ms->input_pos - start
					- 1);
		// tu jest cos nie tak jak jest "la" "-la"
		else
			token->value = ft_substr(ms->input, start, ms->input_pos - start);
	}
}

void	get_token(t_ms *ms, t_token *token)
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
	else if ((ms->input[ms->input_pos] == '\''
			|| ms->input[ms->input_pos] == '\"') && (ms->input[ms->input_pos
				+ 1] == ms->input[ms->input_pos]))
	{
		token->value = ft_strdup("");
		ms->input_pos++;
	}
	else
		get_word_token(ms, token);
}
