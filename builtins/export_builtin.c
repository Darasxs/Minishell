/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:37 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/25 19:32:52 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_env(t_ms *ms, char *env)
{
	size_t	i;

	i = 0;
	while (ms->env_copy[i])
	{
		if (ft_strncmp(ms->env_copy[i], env, ft_strchr(env, '=') - env) == 0)
		{
			free(ms->env_copy[i]);
			ms->env_copy[i] = ft_strdup(env);
			return ;
		}
		i++;
	}
	ms->env_copy[i] = ft_strdup(env);
	ms->env_copy[i + 1] = NULL;
}

void	export_builtin(t_ms *ms)
{
	size_t	i;

	if (!ms->split_commands[1])
	{
		i = 0;
		while (ms->env_copy[i])
		{
			printf("declare -x ");
			printf("%s\n", ms->env_copy[i]);
			i++;
		}
	}
	else
	{
		i = 1;
		while (ms->split_commands[i])
		{
			if (ft_strrchr(ms->split_commands[i], '=') != 0)
				add_new_env(ms, ms->split_commands[i]);
			else
				printf("export: `%s': not a valid identifier\n", ms->split_commands[i]);
			i++;
		}
	}
}
