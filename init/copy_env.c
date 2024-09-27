/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:26:29 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/27 23:26:41 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **copy_envp(char **envp)
{
	size_t i;
	char **copy;

	copy = malloc(100 * sizeof(char *));
	if (!copy)
		return NULL;
	i = 0;
	while (envp[i])
	{
		copy[i] = strdup(envp[i]);
		if (!copy[i])
		{
			while (i--)
				free(copy[i]);
			free(copy);
			return NULL;
		}
		i++;
	}
	copy[i] = NULL;
	return copy;
}
