/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:02 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/30 20:44:22 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BUFFER_SIZE 1024

void	handle_double_input(t_ms *ms, size_t i)
{
	char *eof_delimiter;
	char *buffer;
	char *index_str;
	char *temp_base;

	ms->heredoc = true;
	temp_base = ft_strdup(".heredoc_");
	if (!temp_base)
		return ;
	index_str = ft_itoa(ms->heredoc_counter++);
	if (!index_str)
	{
		free(temp_base);
		return ;
	}
	ms->temp_filename = ft_strjoin(temp_base, index_str);
	free(temp_base);
	free(index_str);
	if (!ms->temp_filename)
		return ;

	eof_delimiter = ms->split_commands[i + 1];
	ms->heredoc_file_descriptor = open(ms->temp_filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ms->heredoc_file_descriptor == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
		free(ms->temp_filename);
		return ;
	}

	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			close(ms->heredoc_file_descriptor);
			free(ms->temp_filename);
			return ;
		}

		if (ft_strncmp(buffer, eof_delimiter, ft_strlen(eof_delimiter)) == 0
			&& ft_strlen(buffer) == ft_strlen(eof_delimiter))
		{
			free(buffer);
			break ;
		}

		write(ms->heredoc_file_descriptor, buffer, ft_strlen(buffer));
		write(ms->heredoc_file_descriptor, "\n", 1);
		free(buffer);
	}

	close(ms->heredoc_file_descriptor);
	ms->heredoc_file_descriptor = open(ms->temp_filename, O_RDONLY);
	if (ms->heredoc_file_descriptor == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ms->split_commands[i + 1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
		free(ms->temp_filename);
		return ;
	}
	ms->heredoc_counter++;
	unlink(ms->temp_filename);
}