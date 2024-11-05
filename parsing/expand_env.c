/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:53:29 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/05 20:22:07 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_env_helper(t_ms *ms, char *env, size_t i)
{
	size_t	k;
	size_t	l;

	k = 0;
	while (ms->env_copy[k])
	{
		l = 0;
		while (ms->env_copy[k][l] != '=')
			l++;
		if (ft_strlen(env) == l && ft_strncmp(env, ms->env_copy[k], l - 1) == 0)
		{
			free(ms->split_commands[i]);
			ms->split_commands[i] = ft_getenv(env, ms);
			free(env);
			break ;
		}
		k++;
	}
}

void	expand_env(t_ms *ms)
{
	size_t	i;
	char	*env;

	i = 0;
	if (ft_strncmp(ms->split_commands[i], "echo", 5) == 0)
		return ;
	while (ms->split_commands[i])
	{
		if (ms->split_commands[i][0] == '$')
		{
			env = ft_substr(ms->split_commands[i], 1,
					ft_strlen(ms->split_commands[i]) + 1);
			expand_env_helper(ms, env, i);
		}
		i++;
	}
}
