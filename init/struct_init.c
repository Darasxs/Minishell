/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:27:48 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 01:16:44 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

minishell_t	*struct_init(char **envp)
{
	minishell_t	*line;
	lst_t		*lst;

	line = malloc(sizeof(minishell_t));
	if (!line)
		ft_error("Error while allocating the memory\n", NULL, line);
	lst = malloc(sizeof(lst_t));
	if (!lst)
	{
		cleanup(line);
		ft_error("Error while allocating the memory\n", NULL, line);
	}
	lst = NULL;
	line->env_copy = copy_envp(envp);
	return (line);
}
