/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:30:13 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/04 16:11:14 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *env, t_ms *ms)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	while (ms->env_copy[i])
	{
		len = ft_strrchr(ms->env_copy[i], '=') - ms->env_copy[i];
		new = ft_substr(ms->env_copy[i], 0, len);
		if (ft_strncmp(new, env, len) == 0)
		{
			j = 0;
			while (ms->env_copy[i][j] != '=')
				j++;
			len = j + 1;
			while (ms->env_copy[i][len])
				len++;
			return (free(new), ft_substr(ms->env_copy[i], j + 1, len));
		}
		free(new);
		i++;
	}
	return (NULL);
}
