/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:37 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/30 09:27:10 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_env(t_minishell *line, t_list **lst)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		ft_error("Error while allocating the memory\n", line);
	node->new_env = malloc(sizeof(char) * (ft_strlen(line->split_commands[0])
				+ 1));
	if (!node->new_env)
		ft_error("Error while allocating the memory for new_env\n", line);
	ft_strlcpy(node->new_env, line->split_commands[0],
		ft_strlen(line->split_commands[0]) + 1);
	node->next = NULL;
	ft_lstadd_back(lst, node);
}

void	update_env_copy(t_minishell *line, t_list *tmp)
{
	size_t	i;

	i = 0;
	while (line->env_copy[i])
		i++;
	line->env_copy[i] = strdup(tmp->new_env);
}

void	export_new_env(t_minishell *line, t_list **lst)
{
	size_t	i;
	t_list	*tmp;
	size_t	j;

	i = 1;
	tmp = *lst;
	while (line->split_commands[i] && tmp && tmp->new_env)
	{
		j = 0;
		while (tmp->new_env[j] && tmp->new_env[j] != '=')
			j++;
		if ((ft_strncmp(line->split_commands[i], tmp->new_env, j - 1) == 0)
			&& (j == ft_strlen(line->split_commands[i])))
		{
			update_env_copy(line, tmp);
			//free the node;
		}
		tmp = tmp->next;
		i++;
	}
}

void	export_builtin(t_minishell *line)
{
	size_t	i;

	i = 0;
	if (ft_strncmp(line->split_commands[0], "export", 7) == 0 && !line->split_commands[1])
	{
		while (line->env_copy[i])
		{
			printf("declare -x ");
			printf("%s\n", line->env_copy[i]);
			i++;
		}
	}
	else if (ft_strrchr(line->split_commands[0], '=') != 0)
	{
		while (line->split_commands[i])
		{
			if (ft_strrchr(line->split_commands[i], '=') != 0)
				add_new_env(line, &(line->lst));
			else
				wrong_command(line->split_commands[i], line);
			i++;
		}
	}
	else
		export_new_env(line, &(line->lst));
}
