/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:55:16 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/18 11:06:55 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_exit_status(t_ms *ms, char *exit_status_str, size_t *j,
		size_t *k)
{
	ft_strlcpy(ms->exit_code + *k, exit_status_str, ft_strlen(exit_status_str)
		+ 1);
	*k += ft_strlen(exit_status_str);
	*j += 2;
}

void	check_for_sign(t_ms *ms, size_t i, size_t *j, size_t *k)
{
	if (ms->split_commands[i][*j] == '$')
	{
		ft_strlcat(ms->exit_code + *k, "$", 2);
		(*k)++;
		(*j)++;
	}
	else if (ms->split_commands[i][*j] == '?')
	{
		ft_strlcat(ms->exit_code + *k, "?", 2);
		(*k)++;
		(*j)++;
	}
	else
		(*k)++;
	(*j)++;
}

void	handle_exit_code(t_ms *ms, size_t i)
{
	size_t	j;
	size_t	k;
	char	*exit_status_str;

	j = 0;
	k = 0;
	exit_status_str = ft_itoa(ms->exit_status);
	ms->exit_code = malloc(ft_strlen(ms->split_commands[i])
			+ ft_strlen(exit_status_str) + 1);
	if (!ms->exit_code)
		ft_error("Error while allocating memory\n", ms);
	while (ms->split_commands[i][j])
	{
		if (ms->split_commands[i][j] == '$' && ms->split_commands[i][j
			+ 1] == '?')
			replace_exit_status(ms, exit_status_str, &j, &k);
		else
			check_for_sign(ms, i, &j, &k);
	}
	ms->exit_code[k] = '\0';
	free(ms->split_commands[i]);
	ms->split_commands[i] = ms->exit_code;
	free(exit_status_str);
}

void	check_exit_code(t_ms *ms)
{
	size_t	i;

	i = 0;
	while (ms->split_commands[i])
	{
		if (ms->split_commands[i][0] == '$' && ms->split_commands[i][1] == '?')
			handle_exit_code(ms, i);
		i++;
	}
}
