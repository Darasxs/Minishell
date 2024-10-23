/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/23 17:37:56 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	syntax_check(t_ms *ms, t_token *token)
{
	(void)ms;
	if (token->value[0] == '>' || token->value[0] == '<')
	{
		if (!token->next->value || (token->next->value[0] != '<'
				&& token->next->value[0] != '>'))
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `%s'\n",
				token->value);
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
		ms->exit_status = 126;
		return (false);
	}
	else if (token->value[0] == '.' && !token->value[3])
	{
		if (token->value[1] == '.' && !token->value[2])
			printf("minishell: ..: command not found\n");
		else
			printf(".: usage: . filename [arguments]\n");
		ms->exit_status = 127;
		return (false);
	}
	// else if (token->next->value[0] == '|'
		//&& token->next->next->value[0] == '|')
	//{
	//	printf("minishell: syntax error near unexpected token '|'\n");
	//	ms->exit_status = 127;
	//	return (false);
	//}
	return (true);
}
