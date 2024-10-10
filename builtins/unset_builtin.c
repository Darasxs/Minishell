/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:34 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/09 20:27:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_builtin(t_minishell *ms)
{
	size_t		i;
	char		*env_variable;
	char		*equal_pos;
	size_t		len;
	size_t		j;

	i = 0;
	while (ms->env_copy[i])
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
				while (ms->env_copy[j])
				{
					ms->env_copy[j] = ms->env_copy[j + 1];
					j++;
				}
				ms->env_copy[j] = NULL;
				return;
			}
			free(env_variable);
		}
		i++;
	}
}
