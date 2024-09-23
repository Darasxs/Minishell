/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:34 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/23 13:41:56 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_builtin(minishell_t *line)
{
	size_t		i;
	char		*env_variable;
	char		*equal_pos;
	size_t		len;
	size_t		j;

	i = 0;
	while (line->env_copy[i])
	{
		equal_pos = ft_strrchr(line->env_copy[i], '=');
		if (equal_pos != NULL)
		{
			len = equal_pos - line->env_copy[i];
			env_variable = ft_substr(line->env_copy[i], 0, len);
			if (ft_strncmp(env_variable, line->split_commands[1], len) == 0)
			{
				free(line->env_copy[i]);
				line->env_copy[i] = NULL;
				j = i;
				while (line->env_copy[j])
				{
					line->env_copy[j] = line->env_copy[j + 1];
					j++;
				}
				line->env_copy[j] = NULL;
				return;
			}
			free(env_variable);
		}
		i++;
	}
}
