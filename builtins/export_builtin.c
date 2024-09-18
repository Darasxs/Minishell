/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:37 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/18 22:45:16 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
}
