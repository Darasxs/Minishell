/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:47 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/09/28 01:38:02 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_exit_status(char **exit_code, char *exit_status_str, size_t *j,
		size_t *k)
{
	ft_strlcpy(*exit_code + *k, exit_status_str, ft_strlen(exit_status_str)
		+ 1);
	*k += ft_strlen(exit_status_str);
	*j += 2;
}

void	append_dollar_sign(char **exit_code, size_t *j, size_t *k)
{
	ft_strlcat(*exit_code + *k, "$", 2);
	(*k)++;
	(*j)++;
}

void	append_question_mark(char **exit_code, size_t *j, size_t *k)
{
	ft_strlcat(*exit_code + *k, "?", 2);
	(*k)++;
	(*j)++;
}

void	check_for_sign(minishell_t *line, char **exit_code, size_t i, size_t *j,
		size_t *k)
{
	if (line->split_commands[i][*j] == '$')
		append_dollar_sign(exit_code, j, k);
	else if (line->split_commands[i][*j] == '?')
		append_question_mark(exit_code, j, k);
}

void	handle_exit_code(minishell_t *line, size_t i)
{
	size_t	j;
	size_t	k;
	char	*exit_status_str;
	char	*exit_code;

	j = 0;
	k = 0;
	exit_status_str = ft_itoa(line->exit_status);
	exit_code = malloc(ft_strlen(line->split_commands[i])
			+ ft_strlen(exit_status_str) + 1);
	if (!exit_code)
		ft_error("Error while allocating memory\n", NULL, line);
	while (line->split_commands[i][j])
	{
		if (line->split_commands[i][j] == '$' && line->split_commands[i][j
			+ 1] == '?')
			replace_exit_status(&exit_code, exit_status_str, &j, &k);
		else
			check_for_sign(line, &exit_code, i, &j, &k);
	}
	exit_code[k] = '\0';
	free(line->split_commands[i]);
	line->split_commands[i] = exit_code;
	free(exit_status_str);
}
