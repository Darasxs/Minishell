/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:26:45 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/27 11:31:01 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	syntax_check(t_ms *ms, t_token *token)
{
	if (token->value[0] == '>' || token->value[0] == '<')
	{
		if (!token->next->value || (token->next->value[0] != '<'
				&& token->next->value[0] != '>'))
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		else
			print_fd("minishell: syntax error near unexpected token `", token->value, "'\n");
		ms->exit_status = 2;
		return (false);
	}
	else if (token->value[0] == '|')
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
		print_fd("minishell: ", ft_getenv("HOME", ms), ": is a directory\n");
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
