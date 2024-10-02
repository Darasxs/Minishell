/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:29:15 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/01 17:13:33 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_struct(t_minishell *line)
{
	free_split(line->split_commands);
	free_split(line->split_pipe);
	free_split(line->env_copy);
	if (line->prompt)
		free(line->prompt);
	if (line->input)
		free(line->input);
	if (line->path)
		free(line->path);
	if (line->env)
		free(line->env);
	if (line->full_path)
		free(line->full_path);
	if (line->exit_code)
		free(line->exit_code);
	if (line->lst->new_env)
		free(line->lst->new_env);
	if (line->lst)
		free(line->lst);
	if (line)
		free(line);
}

void	ft_error(char *str, t_minishell *line)
{
	printf("%s\n", str);
	free_struct(line);
	exit(EXIT_FAILURE);
}

void	wrong_command(char *info, t_minishell *line)
{
	if (info)
		printf("minishell: %s: ", info);
	printf("command not found\n");
	free_struct(line);
	exit(EXIT_FAILURE);
}
