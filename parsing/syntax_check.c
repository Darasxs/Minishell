/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/18 11:13:10 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	syntax_check(t_ms *ms, t_token *token)
{
	(void)ms;
	if ((token->value[0] == '>' || token->value[0] == '<') && !token->next->value)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		ms->exit_status = 2;
		return (false);
	}
	else if (token->value[0] == '|')
	{
		if (token->value[0] == '|' && token->next->value
			&& token->next->value[0] == '|')
			printf("minishell: syntax error near unexpected token '||'\n");
		else
			printf("minishell: syntax error near unexpected token '|'\n");
		ms->exit_status = 2;
		return (false);
	}
	else if (token->value[0] == '~')
	{
		printf("minishell: %s: is a directory\n", getenv("HOME"));
		ms->exit_status = 2;
		return (false);
	}
	else if (token->value[0] == '.' && !token->value[1])
	{
		printf(".: usage: . filename [arguments]\n");
		ms->exit_status = 2;
		return (false);
	}
	return (true);
}
