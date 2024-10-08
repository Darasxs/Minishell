/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:06 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/08 08:37:35 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_input(t_minishell *line, size_t i)
{
	char	*filename;
	int		file_descriptor;

	filename = line->split_commands[i + 1];
	file_descriptor = open(filename, O_RDONLY);
	if(file_descriptor == -1)
		ft_error("Error in '<'.\n", line);
	if(dup2(file_descriptor, STDIN_FILENO) == -1)
	{
		close(file_descriptor);
		ft_error("Error with file descriptor in '<'.\n", line);
	}
	close(file_descriptor);
}
