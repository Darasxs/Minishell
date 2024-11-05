/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:45:02 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/05 18:34:36 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BUFFER_SIZE 1024

t_heredoc	*heredoc_init(int pipe_index)
{
	t_heredoc	*new_heredoc;
	char		*temp_base;
	char		*index_str;

	new_heredoc = malloc(sizeof(t_heredoc));
	if (!new_heredoc)
		return (NULL);
	temp_base = ft_strdup(".heredoc_");
	if (!temp_base)
		return (free(new_heredoc), NULL);
	index_str = ft_itoa(pipe_index);
	if (!index_str)
	{
		free(temp_base);
		free(new_heredoc);
		return (NULL);
	}
	new_heredoc->filename = ft_strjoin(temp_base, index_str);
	new_heredoc->pipe_index = 0;
	new_heredoc->fd = -1;
	free(temp_base);
	free(index_str);
	if (!new_heredoc->filename)
		return (free(new_heredoc), NULL);
	return (new_heredoc);
}

void	heredoc_while_loop(t_heredoc *new_heredoc, char *eof_delimiter)
{
	char	*buffer;

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
}

void	handle_double_input(t_ms *ms, size_t command_index, int pipe_index)
{
	t_heredoc	*new_heredoc;
	char		*eof_delimiter;

	new_heredoc = heredoc_init(pipe_index);
	new_heredoc->fd = open(new_heredoc->filename, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (new_heredoc->fd == -1)
	{
		free(new_heredoc->filename);
		return (free(new_heredoc));
	}
	eof_delimiter = ms->split_commands[command_index + 1];
	if (setup_sigint_ignore() != 0 || setup_sigquit_ignore() != 0)
		return (ft_putstr_fd("Error\n", 2));
	heredoc_while_loop(new_heredoc, eof_delimiter);
	close(new_heredoc->fd);
	new_heredoc->fd = open(new_heredoc->filename, O_RDONLY);
	unlink(new_heredoc->filename);
	new_heredoc->pipe_index = pipe_index;
	new_heredoc->next = ms->heredocs;
	ms->heredocs = new_heredoc;
}

void	double_input_check(t_ms *ms)
{
	t_token	*token;
	int		pipe_index;
	int		i;

	token = ms->token;
	pipe_index = 0;
	while (ms->split_pipes[pipe_index])
	{
		token = create_split_commands(ms, token);
		i = 0;
		while (ms->split_commands[i])
		{
			if (ms->split_commands[i][0] == '<'
				&& ms->split_commands[i][1] == '<')
			{
				handle_double_input(ms, i, pipe_index);
				ms->heredoc_found = true;
			}
			i++;
		}
		free_split(ms->split_commands);
		pipe_index++;
	}
}
