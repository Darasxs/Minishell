/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:06 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/30 15:47:13 by paprzyby         ###   ########.fr       */
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
		exit(ms->exit_status);
	}
	if (dup2(file_descriptor, STDIN_FILENO) == -1)
	{
		close(file_descriptor);
		//ms->exit_status = 1;
		exit(ms->exit_status);
	}
	close(file_descriptor);
}
