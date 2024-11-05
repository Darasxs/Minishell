/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:27:48 by paprzyby          #+#    #+#             */
/*   Updated: 2024/10/08 17:29:35 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	isatty_helper(t_ms *ms)
{
	char	*line;

	if (isatty(fileno(stdin)))
		prompt(ms);
	else
	{
		line = get_next_line(fileno(stdin));
		if (!line)
			return (false);
		ms->input = ft_strtrim(line, "\n");
		free(line);
	}
	return (true);
}

char	**envp_init(char **envp)
{
	size_t	i;
	char	**copy;

	copy = malloc(100 * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i--)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_ms	*minishell_init(char **envp)
{
	t_ms		*ms;
	//t_heredoc	*heredocs;

	ms = malloc(sizeof(t_ms));
	if (!ms)
		ft_error("Error while allocating the memory\n", ms);
	//heredocs = malloc(sizeof(t_heredoc));
	//if (!heredocs)
	//	return (NULL);
	//heredocs->fd = -1;
	//heredocs->pipe_index = 0;
	ms->env_copy = envp_init(envp);
	ms->exit_status = 0;
	ms->input_pos = 0;
	ms->input_len = 0;
	ms->single_q = 0;
	ms->double_q = 0;
	ms->token_count = 0;
	ms->status = 0;
	ms->heredoc_file_descriptor = -1;
	ms->first_iteration = true;
	ms->heredoc = false;
	ms->heredoc_found = false;
	return (ms);
}
