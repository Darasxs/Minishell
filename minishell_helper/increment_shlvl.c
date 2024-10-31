/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:40:44 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/31 15:45:41 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_shlvl(t_ms *ms, char *shlvl_str, size_t i)
{
	char	*new_shlvl;
	char	*new_env;
	int		shlvl;

	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	free(shlvl_str);
	new_shlvl = ft_itoa(shlvl);
	if (new_shlvl)
	{
		new_env = malloc(strlen("SHLVL=") + strlen(new_shlvl) + 1);
		if (new_env)
		{
			ft_strlcpy(new_env, "SHLVL=", 6 + ft_strlen(new_shlvl) + 1);
			ft_strlcat(new_env, new_shlvl, 6 + ft_strlen(new_shlvl) + 1);
			free(ms->env_copy[i]);
			ms->env_copy[i] = new_env;
		}
		free(new_shlvl);
	}
}

void	increment_shlvl(t_ms *ms)
{
	char	*shlvl_str;
	size_t	i;
	char	*equal_pos;
	char	*env_variable;
	size_t	len;

	i = 0;
	shlvl_str = NULL;
	while (ms->env_copy[i])
	{
		equal_pos = ft_strrchr(ms->env_copy[i], '=');
		len = equal_pos - ms->env_copy[i];
		env_variable = ft_substr(ms->env_copy[i], 0, len);
		if (ft_strncmp(env_variable, "SHLVL", len) == 0)
		{
			shlvl_str = ft_strdup(ms->env_copy[i] + 6);
			break ;
		}
		free(env_variable);
		i++;
	}
	if (shlvl_str)
		update_shlvl(ms, shlvl_str, i);
}
