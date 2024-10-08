/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:07 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/08 08:48:31 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_single_output(t_minishell *line, size_t i)
{
	char	*filename;
	int		file_descriptor;

	filename = line->split_commands[i + 1];
	file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(file_descriptor == -1)
		ft_error("Error in '>'.\n", line);
	if(dup2(file_descriptor, STDOUT_FILENO) == -1)
	{
		close(file_descriptor);
		ft_error("Error with file descriptor in '>'.\n", line);
	}
	printf("check\n");
	close(file_descriptor);
}

