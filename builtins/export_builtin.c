/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:37 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/21 13:41:49 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_for_env(minishell_t *line)
{
	if (!line->env_pointer)
		return (false);
	else
		return (true);
}

void	new_env_value(minishell_t *line)
{
	size_t		i;
	char		*env_variable;
	char		*equal_pos;
	size_t		len;
	size_t		j;

	i = 0;
	j = 0;
	while (line->env_copy[i])
	{
		equal_pos = ft_strrchr(line->env_copy[i], '=');
		if (equal_pos != NULL)
		{
			len = equal_pos - line->env_copy[i];
			env_variable = ft_substr(line->env_copy[i], 0, len);
			if (ft_strncmp(env_variable, line->split_commands[1], len) == 0)
			{
				//add a new value for env
			}
			free(env_variable);
		}
		i++;
	}
}

void	export_builtin(minishell_t *line)
{
	size_t	i;

	if (!line->split_commands[1])
	{
		i = 0;
		while (line->env_pointer[i])
		{
			printf("declare -x ");
			printf("%s\n", line->env_pointer[i]);
			i++;
		}
	}
	else
	{
		if (check_for_env(line))
			printf("The env variable already has a value\n");
		else
			new_env_value(line);
	}
}
