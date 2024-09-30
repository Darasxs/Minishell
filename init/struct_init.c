/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:27:48 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/30 10:24:10 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_minishell	*struct_init(char **envp)
{
	t_minishell	*line;
	t_list		*lst;

	line = malloc(sizeof(t_minishell));
	if (!line)
		ft_error("Error while allocating the memory\n", line);
	lst = malloc(sizeof(t_list));
	if (!lst)
		ft_error("Error while allocating the memory\n", line);
	lst = NULL;
	line->env_copy = copy_envp(envp);
	line->exit_status = 0;
	return (line);
}
