/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:47:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/17 15:52:23 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_builtin(minishell_t *line)
{
	int	i;

	i = 0;
	while (line->env_pointer[i])
	{
		printf("%s\n", line->env_pointer[i]);
		i++;
	}
}
