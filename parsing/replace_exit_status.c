/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:47 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/28 05:39:51 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_exit_status(t_minishell *line, char *exit_status_str, size_t *j,
		size_t *k)
{
	ft_strlcpy(line->exit_code + *k, exit_status_str, ft_strlen(exit_status_str)
		+ 1);
	*k += ft_strlen(exit_status_str);
	*j += 2;
}

void	append_dollar_sign(t_minishell *line, size_t *j, size_t *k)
{
	ft_strlcat(line->exit_code + *k, "$", 2);
	(*k)++;
	(*j)++;
}

void	append_question_mark(t_minishell *line, size_t *j, size_t *k)
{
	ft_strlcat(line->exit_code + *k, "?", 2);
	(*k)++;
	(*j)++;
}

void	check_for_sign(t_minishell *line, size_t i, size_t *j,
		size_t *k)
{
	if (line->split_commands[i][*j] == '$')
		append_dollar_sign(line, j, k);
	else if (line->split_commands[i][*j] == '?')
		append_question_mark(line, j, k);
}

void	handle_exit_code(t_minishell *line, size_t i)
{
	size_t	j;
	size_t	k;
	char	*exit_status_str;

	j = 0;
	k = 0;
	exit_status_str = ft_itoa(line->exit_status);
	line->exit_code = malloc(ft_strlen(line->split_commands[i])
			+ ft_strlen(exit_status_str) + 1);
	if (!line->exit_code)
		ft_error("Error while allocating memory\n", NULL, line);
	while (line->split_commands[i][j])
	{
		if (line->split_commands[i][j] == '$' && line->split_commands[i][j
			+ 1] == '?')
			replace_exit_status(line, exit_status_str, &j, &k);
		else
			check_for_sign(line, i, &j, &k);
	}
	line->exit_code[k] = '\0';
	free(line->split_commands[i]);
	line->split_commands[i] = line->exit_code;
	free(exit_status_str);
}
