/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:29:15 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/25 20:00:01 by paprzyby         ###   ########.fr       */
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
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(info, 2);
	}
	ft_putstr_fd(": command not found\n", 2);
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

void	print_fd(char *str1, char *str2, char *str3)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str1, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
}
