/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:29:15 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/28 01:39:42 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	if (split)
		free(split);
}

void	cleanup(minishell_t *line)
{
	free(line->input);
	free(line->prompt);
}

void	ft_error(char *str, char *info, minishell_t *line)
{
	if (line->split_commands)
		free_split(line->split_commands);
	if (line->split_pipe)
		free_split(line->split_pipe);
	printf("%s", str);
	if (info)
		printf("%s\n", info);
	exit(EXIT_FAILURE);
}
