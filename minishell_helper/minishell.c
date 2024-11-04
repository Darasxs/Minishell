/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 07:19:57 by paprzyby          #+#    #+#             */
/*   Updated: 2024/11/04 11:58:53 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_child_process(t_ms *ms, int i, int *input_fd, int *fd)
{
	t_heredoc	*current_heredoc;

	if (setup_sigquit() != 0)
	{
		free_struct(ms);
		return ;
	}
	ms->heredoc_found = false;
	current_heredoc = ms->heredocs;
	while (current_heredoc)
	{
		if (current_heredoc->pipe_index == i)
		{
			if (dup2(current_heredoc->fd, STDIN_FILENO) == -1)
			{
				write(STDERR_FILENO,
					"Error duplicating file descriptor for heredoc\n", 47);
				return ;
			}
			close(current_heredoc->fd);
			ms->heredoc_found = true;
			break ;
		}
		current_heredoc = current_heredoc->next;
	}
	if (check_if_redirections(ms))
		handle_redirections(ms);
	if (!ms->heredoc_found && i > 0)
	{
		dup2(*input_fd, STDIN_FILENO);
		close(*input_fd);
	}
	if (ms->split_pipes[i + 1])
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	close(fd[0]);
	if (check_builtin(ms))
		handle_builtins(ms, i, input_fd, fd);
	else
		execute_command(ms);
	exit(ms->exit_status);
}

void	handle_parent_process(t_ms *ms, int i, int *input_fd, int *fd)
{
	if (ms->split_pipes[i + 1])
	{
		close(fd[1]);
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		*input_fd = fd[0];
	}
	else
	{
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		close(fd[0]);
	}
}

void	execute_pipe_commands(t_ms *ms, int *input_fd, int i)
{
	int		fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	if (ms->split_pipes[i + 1] && pipe(fd) == -1)
		ft_error("Error occurred while creating a pipe\n", ms);
	check_exit_code(ms);
	if (check_cd_and_unset(ms))
		handle_cd_and_unset(ms, i, input_fd, fd);
	else if (ft_strncmp(ms->split_commands[0], "exit", 5) == 0)
		exit_builtin(ms);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			free(ms->input);
			ft_error("Error occurred while forking\n", ms);
		}
		else if (pid == 0)
			handle_child_process(ms, i, input_fd, fd);
		else
			handle_parent_process(ms, i, input_fd, fd);
	}
}
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

void	minishell(t_ms *ms)
{
	int		status;
	int		input_fd;
	size_t	i;
	t_token	*token;
	int		pipe_index;

	input_fd = STDIN_FILENO;
	token = ms->token;
	create_split_pipes(ms, token);
	if (setup_sigint_ignore() != 0)
	{
		free_struct(ms);
		return ;
	}
	pipe_index = 0;
	while (ms->split_pipes[pipe_index])
	{
		token = create_split_commands(ms, token);
		i = 0;
		while (ms->split_commands[i])
		{
			if (ms->split_commands[i][0] == '<'
				&& ms->split_commands[i][1] == '<')
				handle_double_input(ms, i, pipe_index);
			i++;
		}
		free_split(ms->split_commands);
		pipe_index++;
	}
	i = 0;
	token = ms->head;
	while (ms->split_pipes[i])
	{
		token = create_split_commands(ms, token);
		if (!syntax_check(ms))
			return ;
		execute_pipe_commands(ms, &input_fd, i);
		free_split(ms->split_commands);
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			ms->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ms->exit_status = 128 + WTERMSIG(status);
	}
	cleanup_heredocs(ms);
	free_list(ms, ms->token);
	if (setup_sigint() != 0)
	{
		free_struct(ms);
		return ;
	}
}
