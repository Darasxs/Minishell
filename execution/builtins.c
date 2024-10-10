/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:27:39 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/10 18:50:01 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_minishell *ms, t_token *token)
{
	if (!token->value)
		return ;
	else if (ft_strncmp(token->value, "unset", 6) == 0
		&& ms->split_commands[1])
		unset_builtin(ms);
	else if (ft_strncmp(token->value, "exit", 5) == 0)
		exit_builtin(ms);
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		echo_builtin(ms);
	else
		export_builtin(ms);
}

bool	check_builtin(t_minishell *ms, t_token *token)
{
	if (!token->value)
		return (false);
	else if (token->value[0] && ft_strncmp(token->value,
			"cd", 3) == 0)
		return (true);
	else if (ft_strncmp(token->value, "unset", 6) == 0
		&& ms->split_commands[1])
		return (true);
	else if (ft_strncmp(token->value, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(token->value, "exit", 5) == 0)
		return (true);
	else if (ft_strrchr(token->value, '=') != 0)
		return (true);
	else if (ft_strncmp(token->value, "echo", 5) == 0)
		return (true);
	return (false);
}
