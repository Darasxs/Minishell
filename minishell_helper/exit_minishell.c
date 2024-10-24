/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:29:15 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/23 17:18:10 by paprzyby         ###   ########.fr       */
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

void	free_struct(t_ms *ms)
{
	free_split(ms->env_copy);
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	if (ms->path)
		free(ms->path);
	if (ms->full_path)
		free(ms->full_path);
	if (ms->exit_code)
		free(ms->exit_code);
	if (ms)
		free(ms);
}

void	ft_error(char *str, t_ms *ms)
{
	printf("%s\n", str);
	free_struct(ms);
	exit(ms->exit_status);
}

void	wrong_command(char *info, t_ms *ms)
{
	if (info)
		printf("minishell: %s: ", info);
	printf("command not found\n");
	free_struct(ms);
	ms->exit_status = 127;
}

void	cleanup(t_ms *ms)
{
	ms->double_q = 0;
	ms->single_q = 0;
	ms->first_iteration = true;
	ms->input_pos = 0;
	ms->token_count = 0;
}

void	free_list(t_ms *ms, t_token *token)
{
	token = ms->head;
	while (token->value)
	{
		free(token->value);
		token->value = NULL;
		if (token->next)
			token = token->next;
	}
	free(token);
}
