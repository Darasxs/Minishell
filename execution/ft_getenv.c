/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:30:13 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/25 16:15:32 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *env, t_ms *ms)
{
	char	*value;
	int		i;
	char	*equal_pos;
	char	*env_variable;
	int		len;
	int		j;

	i = 0;
	while (ms->env_copy[i])
	{
		equal_pos = ft_strrchr(ms->env_copy[i], '=');
		len = equal_pos - ms->env_copy[i];
		env_variable = ft_substr(ms->env_copy[i], 0, len);
		if (ft_strncmp(env_variable, env, len) == 0)
		{
			j = 0;
			while (ms->env_copy[i][j - 1] != '=')
				j++;
			len = j;
			while (ms->env_copy[i][len])
				len++;
			value = ft_substr(ms->env_copy[i], j, len);
			return (value);
		}
		free(env_variable);
		i++;
	}
	return (NULL);
}
