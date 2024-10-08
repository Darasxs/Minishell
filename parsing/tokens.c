/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:56:13 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/09 20:29:41 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_quotes(t_minishell *ms)
{
	if (ms->input[ms->input_pos] == '\'' && !ms->single_q && !ms->double_q)
		ms->single_q = 1;
	else if (ms->input[ms->input_pos] == '\"' && !ms->single_q && !ms->double_q)
		ms->double_q = 1;
	else if (ms->input[ms->input_pos] == '\'' && ms->single_q && !ms->double_q)
		ms->single_q = 0;
	else if (ms->input[ms->input_pos] == '\"' && ms->double_q && !ms->single_q)
		ms->double_q = 0;
}

void	get_word_token(t_minishell *ms, t_token *token)
{
	int	start;

	start = ms->input_pos;
	while (ms->input[ms->input_pos])
	{
		if (ms->input[ms->input_pos] == '\'' || ms->input[ms->input_pos] == '\"')
			count_quotes(ms);
		if ((is_space(ms)
				|| ms->input[ms->input_pos] == '|' || ms->input[ms->input_pos] == '<'
				|| ms->input[ms->input_pos] == '>') && !(ms->single_q || ms->double_q))
				// to samo ale dla quotes ale nie w kazdym przypadku
			break;
		ms->input_pos++;
	}
	if (ms->single_q || ms->double_q)
	{
		while (1)
			readline("> ");
		//token->value = ft_strdup("Unclosed quotes");
		//ft_error("Error: Quote is open\n", ms);
	}
	else
		token->value = ft_substr(ms->input, start, ms->input_pos - start);
		// jak jest quotes start + 1 i end - 1
}

void	get_token(t_minishell *ms, t_token *token)
{
	if (ms->input[ms->input_pos] == '|')
		token->value = ft_strdup("|");
	else if (ms->input[ms->input_pos + 1] == '<' && ms->input[ms->input_pos] == '<')
	{
		token->value = ft_strdup("<<");
		ms->input_pos++;
	}
	else if (ms->input[ms->input_pos] == '<')
		token->value = ft_strdup("<");
	else if (ms->input[ms->input_pos + 1] == '>' && ms->input[ms->input_pos] == '>')
	{
		token->value = ft_strdup(">>");
		ms->input_pos++;
	}
	else if (ms->input[ms->input_pos] == '>')
		token->value = ft_strdup(">");
	else if ((ms->input[ms->input_pos] == '\'' || ms->input[ms->input_pos] == '\"')
			&& (ms->input[ms->input_pos + 1] == ms->input[ms->input_pos]))
		empty_quotes(ms, token);
	else
		get_word_token(ms, token);
}
