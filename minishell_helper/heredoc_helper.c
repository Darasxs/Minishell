/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:43:59 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/06 15:24:19 by dpaluszk         ###   ########.fr       */
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
				return (ft_putstr_fd("Error\n", 2));
			close(current_heredoc->fd);
			ms->heredoc_found = true;
			break ;
		}
		current_heredoc = current_heredoc->next;
	}
}
t_heredoc	*heredoc_init_helper(t_heredoc *new_heredoc)
{
	new_heredoc->pipe_index = 0;
	new_heredoc->fd = -1;
	new_heredoc->next = NULL;
	return (new_heredoc);
}