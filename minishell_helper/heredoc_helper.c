/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:43:59 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/05 16:07:22 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_heredocs(t_ms *ms)
{
	t_heredoc	*current;
	t_heredoc	*next;

	current = ms->heredocs;
	while (current)
	{
		next = current->next;
		close(current->fd);
		free(current->filename);
		free(current);
		current = next;
	}
	ms->heredocs = NULL;
}

void	heredoc_setup(t_ms *ms, int i)
{
	t_heredoc	*current_heredoc;

	ms->heredoc_found = false;
	current_heredoc = ms->heredocs;
	while (current_heredoc)
	{
		if (current_heredoc->pipe_index == i)
		{
			if (dup2(current_heredoc->fd, STDIN_FILENO) == -1)
			{
				ft_putstr_fd("Error while duplicating file descriptor\n", 2);
				return ;
			}
			close(current_heredoc->fd);
			ms->heredoc_found = true;
			break ;
		}
		current_heredoc->next = malloc(sizeof(t_heredoc));
		if (!current_heredoc)
			ft_error("Error while allocating the memory\n", ms);
		current_heredoc = current_heredoc->next;
		current_heredoc->filename = NULL;
		current_heredoc->pipe_index = 0;
		current_heredoc->fd = -1;
	}
}
