/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:29:15 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/09 20:41:09 by paprzyby         ###   ########.fr       */
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

void	free_struct(t_minishell *ms)
{
	//free_split(ms->split_commands);
	//free_split(ms->split_pipe);
	free_split(ms->env_copy);
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	if (ms->path)
		free(ms->path);
	if (ms->env)
		free(ms->env);
	if (ms->full_path)
		free(ms->full_path);
	if (ms->exit_code)
		free(ms->exit_code);
	//if (ms->lst->new_env)
	//	free(ms->lst->new_env);
	if (ms->lst)
		free(ms->lst);
	if (ms)
		free(ms);
}

void	ft_error(char *str, t_minishell *ms)
{
	printf("%s\n", str);
	free_struct(ms);
	exit(EXIT_FAILURE);
}

void	wrong_command(char *info, t_minishell *ms)
{
	if (info)
		printf("minishell: %s: ", info);
	printf("command not found\n");
	free_struct(ms);
	exit(EXIT_FAILURE);
}
