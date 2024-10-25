/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:05 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/24 18:36:17 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_double_output(t_ms *ms, size_t i)
{
	char	*filename;
	int		file_descriptor;

	filename = ms->split_commands[i + 1];
	file_descriptor = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_descriptor == -1)
	{
		ms->exit_status = 1;
		ft_error("minishell: syntax error near unexpected token `newline''", ms);
	}
	if (dup2(file_descriptor, STDOUT_FILENO) == -1)
	{
		close(file_descriptor);
		ms->exit_status = 1;
		ft_error("Error with file descriptor in '>>'", ms);
	}
	close(file_descriptor);
}
