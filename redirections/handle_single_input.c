/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:06 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/29 12:11:38 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_input(t_ms *ms, size_t i)
{
	char	*filename;
	int		file_descriptor;

	filename = ms->split_commands[i + 1];
	file_descriptor = open(filename, O_RDONLY);
	if (file_descriptor == -1)
	{
		ms->exit_status = 1;
		ft_error("Error in '<'.\n", ms);
	}
	if (dup2(file_descriptor, STDIN_FILENO) == -1)
	{
		close(file_descriptor);
		ms->exit_status = 1;
		ft_error("Error with file descriptor in '<'.\n", ms);
	}
	close(file_descriptor);
}
