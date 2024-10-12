/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:27:48 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/08 17:29:35 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**envp_init(char **envp)
{
	size_t	i;
	char	**copy;

	copy = malloc(100 * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i--)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_minishell	*minishell_init(char **envp)
{
	t_minishell	*ms;
	t_list		*lst;

	ms = malloc(sizeof(t_minishell));
	if (!ms)
		ft_error("Error while allocating the memory\n", ms);
	lst = malloc(sizeof(t_list));
	if (!lst)
		ft_error("Error while allocating the memory\n", ms);
	lst = NULL;
	ms->env_copy = envp_init(envp);
	ms->exit_status = 0;
	ms->input_pos = 0;
	ms->single_q = 0;
	ms->double_q = 0;
	ms->first_iteration = true;
	ms->token_count = 0;
	return (ms);
}
