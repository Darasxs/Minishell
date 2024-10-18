/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:07 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/18 11:11:10 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_output(t_ms *ms, size_t i)
{
	char	*filename;
	int		file_descriptor;

	filename = ms->split_commands[i + 1];
	file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_descriptor == -1)
		ft_error("Error in '>'.\n", ms);
	if (dup2(file_descriptor, STDOUT_FILENO) == -1)
	{
		close(file_descriptor);
		ft_error("Error with file descriptor in '>'.\n", ms);
	}
	close(file_descriptor);
}
