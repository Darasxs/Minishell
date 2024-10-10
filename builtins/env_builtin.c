/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:47:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/09 20:27:58 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_builtin(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->env_copy[i])
	{
		printf("%s\n", ms->env_copy[i]);
		i++;
	}
}
