/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:04:37 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 01:10:40 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_env(minishell_t *line, lst_t **lst)
{
	lst_t	*node;

	node = malloc(sizeof(lst_t));
	if (!node)
		ft_error("Error while allocating the memory\n", NULL, line);
	node->new_env = malloc(sizeof(char) * (ft_strlen(line->split_commands[0])
				+ 1));
	if (!node->new_env)
		ft_error("Error while allocating the memory for new_env\n", NULL, line);
	ft_strlcpy(node->new_env, line->split_commands[0],
		ft_strlen(line->split_commands[0]) + 1);
	node->next = NULL;
	ft_lstadd_back(lst, node);
}

void	update_env_copy(minishell_t *line, lst_t *tmp)
{
	size_t	i;

	i = 0;
	while (line->env_copy[i])
		i++;
	line->env_copy[i] = strdup(tmp->new_env);
}

void	export_new_env(minishell_t *line, lst_t **lst)
{
	size_t	i;
	lst_t	*tmp;
	size_t	j;

	i = 1;
	tmp = *lst;
	//(*lst)->prev = NULL;
	while (line->split_commands[i] && tmp && tmp->new_env)
	{
		j = 0;
		while (tmp->new_env[j] && tmp->new_env[j] != '=')
			j++;
		if ((ft_strncmp(line->split_commands[i], tmp->new_env, j - 1) == 0)
			&& (j == ft_strlen(line->split_commands[i])))
		{
			update_env_copy(line, tmp);
			//free the node

			//if ((*lst)->prev == NULL)
			//	*lst = tmp->next;
			//else
			//	(*lst)->prev->next = tmp->next;
			//free(tmp->new_env);
			//free(tmp);
			//if ((*lst)->prev == NULL)
			//	tmp = *lst;
			//else
			//	tmp = (*lst)->prev->next;
		}
		tmp = tmp->next;
		i++;
	}
}

void	export_builtin(minishell_t *line)
{
	size_t	i;

	i = 0;
	if (!line->split_commands[1])
	{
		if (ft_strrchr(line->split_commands[0], '=') == 0)
		{
			if (ft_strncmp(line->split_commands[0], "export", 7) == 0)
			{
				i = 0;
				while (line->env_copy[i])
				{
					printf("declare -x ");
					printf("%s\n", line->env_copy[i]);
					i++;
				}
			}
			//else
			//	ft_error("Command not found\n", NULL, line);
		}
		else
			add_new_env(line, &(line->lst));
	}
	else
		export_new_env(line, &(line->lst));
}
