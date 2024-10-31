/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:02 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/10/31 17:57:34 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BUFFER_SIZE 1024

void	handle_double_input(t_ms *ms, size_t command_index, int pipe_index)
{
	t_heredoc	*new_heredoc;
	char		*eof_delimiter;
	char		*buffer;
	char		*temp_base;
	char		*index_str;


	new_heredoc = malloc(sizeof(t_heredoc));
	if (!new_heredoc)
		return ;
	temp_base = ft_strdup(".heredoc_");
	if (!temp_base)
	{
		free(new_heredoc);
		return ;
	}
	index_str = ft_itoa(pipe_index);
	if (!index_str)
	{
		free(temp_base);
		free(new_heredoc);
		return ;
	}
	new_heredoc->filename = ft_strjoin(temp_base, index_str);
	free(temp_base);
	free(index_str);
	if (!new_heredoc->filename)
	{
		free(new_heredoc);
		return ;
	}
	new_heredoc->fd = open(new_heredoc->filename, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (new_heredoc->fd == -1)
	{
		free(new_heredoc->filename);
		free(new_heredoc);
		return ;
	}
	eof_delimiter = ms->split_commands[command_index + 1];
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			close(new_heredoc->fd);
			break ;
		}
		if (ft_strncmp(buffer, eof_delimiter, ft_strlen(eof_delimiter)) == 0
			&& ft_strlen(buffer) == ft_strlen(eof_delimiter))
		{
			free(buffer);
			break ;
		}
		write(new_heredoc->fd, buffer, ft_strlen(buffer));
		write(new_heredoc->fd, "\n", 1);
		free(buffer);
	}
	close(new_heredoc->fd);
	new_heredoc->fd = open(new_heredoc->filename, O_RDONLY);
	unlink(new_heredoc->filename);
	new_heredoc->pipe_index = pipe_index;
	new_heredoc->next = ms->heredocs;
	ms->heredocs = new_heredoc;
}
