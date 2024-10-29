/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:34 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/29 15:05:03 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_builtin(t_ms *ms)
{
	size_t	i;
	char	*env_variable;
	char	*equal_pos;
	size_t	len;
	size_t	j;

	i = 0;
	if (ms->split_commands[1] && (ms->split_commands[1][0] == '\0' || ms->split_commands[1][0] == '='
		|| ms->split_commands[1][0] == '$'))
	{
		ft_putstr_fd("minishell: unset: `<': not a valid identifier\n", 2);
		ft_putstr_fd("minishell: unset: `>': not a valid identifier\n", 2);
		ms->exit_status = 1;
		return ;
	}
	else if (ms->split_commands[1] && ms->split_commands[1][0] == '?' && ms->split_commands[1][1] == '\0')
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(ms->split_commands[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		ms->exit_status = 1;
		return ;
	}
	while (ms->env_copy[i] && ms->split_commands[1])
	{
		equal_pos = ft_strrchr(ms->env_copy[i], '=');
		if (equal_pos != NULL)
		{
			len = equal_pos - ms->env_copy[i];
			env_variable = ft_substr(ms->env_copy[i], 0, len);
			if (ft_strncmp(env_variable, ms->split_commands[1], len) == 0)
			{
				free(ms->env_copy[i]);
				ms->env_copy[i] = NULL;
				j = i;
				while (ms->env_copy[j + 1])
				{
					ms->env_copy[j] = ms->env_copy[j + 1];
					j++;
				}
				ms->env_copy[j] = NULL;
				return ;
			}
			free(env_variable);
		}
		i++;
	}
}
