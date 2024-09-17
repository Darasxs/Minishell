/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:34 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/17 16:39:15 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_builtin(minishell_t *line)
{
	int	i;

	i = 0;
	while (ft_strncmp(line->split_commands[1], line->env_pointer[i], ft_strlen(line->env_pointer[i])) != 0)
	{
		printf("%s\n", line->env_pointer[i]);
		i++;
	}
	if (line->env_pointer[i])
		printf("(null)\n");
	else
		printf("not null\n");
}
