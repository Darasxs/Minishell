/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:27:48 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 05:26:31 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_minishell	*struct_init(char **envp)
{
	t_minishell	*line;
	t_list		*lst;

	line = malloc(sizeof(t_minishell));
	if (!line)
		ft_error("Error while allocating the memory\n", NULL, line);
	lst = malloc(sizeof(t_list));
	if (!lst)
	{
		cleanup(line);
		ft_error("Error while allocating the memory\n", NULL, line);
	}
	lst = NULL;
	line->env_copy = copy_envp(envp);
	return (line);
}
