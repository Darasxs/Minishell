/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/17 20:04:21 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	syntax_check(t_minishell *ms, t_token *token)
{
	(void)ms;
	if (token->value[0] == '>' || token->value[0] == '<')
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (false);
	}
	else if (token->value[0] == '|')
	{
		if (token->value[0] == '|' && token->next->value && token->next->value[0] == '|')
			printf("minishell: syntax error near unexpected token '||'\n");
		else
			printf("minishell: syntax error near unexpected token '|'\n");
		return (false);
	}
	//else if (token->value[0] == '>' || token->value[0] == '<')
	//{
	//	if (token->next->next->next->value && (token->next->next->next->value[0] == '>' || token->next->next->next->value[0] == '<'))
	//	{
	//		while (token->value)
	//		{
	//			printf("%s\n", )
	//		}
	//	}
	//}
	else if (token->value[0] == '~')
	{
		printf("minishell: %s: is a directory\n", getenv("HOME"));
		return (false);
	}
	else if (token->value[0] == '.' && !token->value[1])
	{
		printf(".: usage: . filename [arguments]\n");
		return (false);
	}
	return (true);
}
