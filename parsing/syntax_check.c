/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/29 12:26:49 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	syntax_check(t_ms *ms, t_token *token)
{
	//if (token->value[0] == '>' || token->value[0] == '<')
	//{
	//	if (!token->next->value || (token->next->value[0] != '<'
	//			&& token->next->value[0] != '>'))
	//		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	//	else
	//	{
	//		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	//		ft_putstr_fd(token->value, 2);
	//		ft_putstr_fd("'\n", 2);
	//	}
	//	ms->exit_status = 2;
	//	return (false);
	//}
	if (token->value[0] == '|')
	{
		if (token->value[0] == '|' && token->next->value
			&& token->next->value[0] == '|')
			ft_putstr_fd("minishell: syntax error near unexpected token '||'\n", 2);
		else
			ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 2);
		ms->exit_status = 2;
		return (false);
	}
	else if (token->value[0] == '~')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ft_getenv("HOME", ms), 2);
		ft_putstr_fd(": is a directory\n", 2);
		ms->exit_status = 126;
		return (false);
	}
	else if (token->value[0] == '.' && !token->value[3])
	{
		if (token->value[1] == '.' && !token->value[2])
			ft_putstr_fd("minishell: ..: command not found\n", 2);
		else
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
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
