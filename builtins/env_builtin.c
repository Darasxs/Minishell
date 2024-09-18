/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:47:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/18 22:34:40 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_builtin(minishell_t *line)
{
	int	i;

	i = 0;
	while (line->env_copy[i])
	{
		printf("%s\n", line->env_copy[i]);
		i++;
	}
}
