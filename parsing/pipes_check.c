/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:35:02 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/31 15:35:18 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	pipes_check(t_ms *ms, t_token *token)
{
	if (token->value[0] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(&token->value[0], 2);
		ft_putstr_fd("'\n", 2);
		ms->exit_status = 2;
		return (false);
	}
	else
	{
		while (token->next->value)
			token = token->next;
		if (token->value[0] == '|')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(&token->value[0], 2);
			ft_putstr_fd("'\n", 2);
			token = ms->head;
			ms->exit_status = 2;
			return (false);
		}
	}
	return (true);
}
