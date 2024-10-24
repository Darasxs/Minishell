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

t_list	*list_init(t_ms *ms)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
	{
		free(ms);
		ft_error("Error while allocating the memory\n", ms);
	}
	lst = NULL;
	return (lst);
}

//char	**envp_names(char **envp)
//{

//}

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

t_ms	*minishell_init(char **envp)
{
	t_ms	*ms;
	t_list	*lst;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		ft_error("Error while allocating the memory\n", ms);
	lst = list_init(ms);
	ms->env_copy = envp_init(envp);
	ms->split_env = NULL;
	ms->prompt = NULL;
	ms->input = NULL;
	ms->path = NULL;
	ms->env = NULL;
	ms->full_path = NULL;
	ms->exit_code = NULL;
	ms->exit_status = 0;
	ms->input_pos = 0;
	ms->input_len = 0;
	ms->single_q = 0;
	ms->double_q = 0;
	ms->token_count = 0;
	ms->split_commands = NULL;
	ms->split_pipes = NULL;
	ms->first_iteration = true;
	return (ms);
}
