/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:29:15 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/05 18:28:11 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	if (split[i])
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

void	exit_minishell(t_ms *ms)
{
	free_split(ms->env_copy);
	free(ms);
}

void	ft_error(char *str, t_ms *ms)
{
	printf("%s\n", str);
	exit(ms->exit_status);
}

void	cleanup(t_ms *ms)
{
	ms->double_q = 0;
	ms->single_q = 0;
	ms->first_iteration = true;
	ms->input_pos = 0;
	ms->token_count = 0;
	free_list(ms, ms->token);
}

void	free_list(t_ms *ms, t_token *token)
{
	t_token	*current;
	t_token	*next;

	(void)token;
	current = ms->head;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	ms->head = NULL;
}
