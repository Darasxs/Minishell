/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:37 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/16 17:17:04 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_env(t_minishell *ms, t_list **lst)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		ft_error("Error while allocating the memory\n", ms);
	node->new_env = malloc(sizeof(char) * (ft_strlen(ms->split_commands[0])
				+ 1));
	if (!node->new_env)
		ft_error("Error while allocating the memory for new_env\n", ms);
	ft_strlcpy(node->new_env, ms->split_commands[0],
		ft_strlen(ms->split_commands[0]) + 1);
	node->next = NULL;
	ft_lstadd_back(lst, node);
}

void	update_env_copy(t_minishell *ms, t_list *tmp)
{
	size_t	i;

	i = 0;
	while (ms->env_copy[i])
		i++;
	ms->env_copy[i] = strdup(tmp->new_env);
}

void	export_new_env(t_minishell *ms, t_list **lst)
{
	size_t	i;
	t_list	*tmp;
	size_t	j;

	i = 1;
	tmp = *lst;
	while (ms->split_commands[i] && tmp && tmp->new_env)
	{
		j = 0;
		while (tmp->new_env[j] && tmp->new_env[j] != '=')
			j++;
		if ((ft_strncmp(ms->split_commands[i], tmp->new_env, j - 1) == 0)
			&& (j == ft_strlen(ms->split_commands[i])))
			update_env_copy(ms, tmp);
		tmp = tmp->next;
		i++;
	}
}

void	export_builtin(t_minishell *ms)
{
	size_t	i;

	i = 0;
	if (ft_strncmp(ms->split_commands[0], "export", 7) == 0 && !ms->split_commands[1])
	{
		while (ms->env_copy[i])
		{
			printf("declare -x ");
			printf("%s\n", ms->env_copy[i]);
			i++;
		}
	}
	else if (ft_strrchr(ms->split_commands[0], '=') != 0)
	{
		while (ms->split_commands[i])
		{
			if (ft_strrchr(ms->split_commands[i], '=') != 0)
				add_new_env(ms, &(ms->lst));
			else
				wrong_command(ms->split_commands[i], ms);
			i++;
		}
	}
	else
		export_new_env(ms, &(ms->lst));
}
