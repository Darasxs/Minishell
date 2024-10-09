/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:56:13 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/09 16:41:24 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_quotes(t_minishell *line)
{
	if (line->input[line->input_pos] == '\'' && !line->single_q && !line->double_q)
		line->single_q = 1;
	else if (line->input[line->input_pos] == '\"' && !line->single_q && !line->double_q)
		line->double_q = 1;
	else if (line->input[line->input_pos] == '\'' && line->single_q && !line->double_q)
		line->single_q = 0;
	else if (line->input[line->input_pos] == '\"' && line->double_q && !line->single_q)
		line->double_q = 0;
}

void	get_word_token(t_minishell *line, t_token *token)
{
	int	start;

	start = line->input_pos;
	while (line->input[line->input_pos])
	{
		if (line->input[line->input_pos] == '\'' || line->input[line->input_pos] == '\"')
			count_quotes(line);
		if ((is_space(line)
				|| line->input[line->input_pos] == '|' || line->input[line->input_pos] == '<'
				|| line->input[line->input_pos] == '>') && !(line->single_q || line->double_q))
				// to samo ale dla quotes ale nie w kazdym przypadku
			break;
		line->input_pos++;
	}
	if (line->single_q || line->double_q)
	{
		while (1)
			readline("> ");
		//token->value = ft_strdup("Unclosed quotes");
		//ft_error("Error: Quote is open\n", line);
	}
	else
		token->value = ft_substr(line->input, start, line->input_pos - start);
		// jak jest quotes start + 1 i end - 1
}

void	get_token(t_minishell *line, t_token *token)
{
	if (line->input[line->input_pos] == '|')
		token->value = ft_strdup("|");
	else if (line->input[line->input_pos + 1] == '<' && line->input[line->input_pos] == '<')
	{
		token->value = ft_strdup("<<");
		line->input_pos++;
	}
	else if (line->input[line->input_pos] == '<')
		token->value = ft_strdup("<");
	else if (line->input[line->input_pos + 1] == '>' && line->input[line->input_pos] == '>')
	{
		token->value = ft_strdup(">>");
		line->input_pos++;
	}
	else if (line->input[line->input_pos] == '>')
		token->value = ft_strdup(">");
	else if ((line->input[line->input_pos] == '\'' || line->input[line->input_pos] == '\"')
			&& (line->input[line->input_pos + 1] == line->input[line->input_pos]))
		empty_quotes(line, token);
	else
		get_word_token(line, token);
}
